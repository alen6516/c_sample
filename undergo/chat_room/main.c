#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>                 // access()
#include <assert.h>
#include <time.h>                   // time_t, time()
#include <errno.h>
#include <signal.h>                 // signal()
#include <pthread.h>

#include <sys/socket.h>             /* socket(), bind(), listen(), ... */
#include <netinet/in.h>             /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>              /* hton(), inet_ntop() */
#include <unistd.h>                 /* read(), write(), close() */
#include <sys/fcntl.h>              /* fcntl() */
#include <sys/poll.h>               /* struct pollfd */

#include "table.h"
#include "conn.h"
#include "util.h"
#include "poll_event.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_FD_NUM  200
#define BACKLOG     128
#define BUFF_SIZE   100


char server_ip[12];
unsigned short server_port;
int backlog;
struct pollfd fd_arr[MAX_FD_NUM];
int curr_fd_num = 0;    // num of fd, including listen_fd


table_t *table;


void sig_hander(int sig)
{
    printf("\n================================\n");
    printf("curr_fd_num = %d, fd_arr = [ ", curr_fd_num);
    for (int i=0; i<curr_fd_num; i++) {
        printf("%d ", fd_arr[i].fd);
    }
    printf("]\n");
    printf("================================\n");
}


void broadcast_msg(int curr_fd_num, int listen_fd, int this_fd, char *send_buff)
{
    int rc = 0;
    for (int j=0; j<curr_fd_num; j++) {
        if (fd_arr[j].fd == listen_fd || fd_arr[j].fd == this_fd) continue;
        rc = send(fd_arr[j].fd, send_buff, BUFF_SIZE, 0);
        if (rc < 0) {
            perror("fail in send()");
        }
    }
}

int main (int argc, char *argv[]) {

    table = init_table();
    if (!table) {
        printf("fail in malloc for table\n");
        exit(1);
    }

    int rc;  
    int on = 1;
    int listen_fd = -1, this_fd = -1;
    struct sockaddr_in serv_addr;
    int timeout;
    int curr_fd_num = 0;        // including listen_fd

    char rece_buff[BUFF_SIZE];
    char send_buff[BUFF_SIZE];
    int rece_len;

    int end_server = 0;
    int close_conn = 0;


    strcpy(server_ip, SERVER_IP);
    server_port = (unsigned short)SERVER_PORT;
    backlog = BACKLOG;
    
    // register handler
    signal(SIGTSTP, sig_hander);    // ctrl-z

    /* create listen_fd */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("fail in creating listen_fd");
        exit(-1);
    }


    /* set socket reuse */
    rc = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof(on));
    if (rc) {
        perror("fail in set socket reuse");
        exit(-1);
    }

    /* set socket non-blocking */
    rc = fcntl(listen_fd, F_SETFL, O_NONBLOCK);
    if (rc < 0) {
        perror("fail in set socket non-blocking");
        close(listen_fd);
        exit(-1);
    }

    /* config socket */
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &(serv_addr.sin_addr.s_addr));
    serv_addr.sin_port = htons(9000);

    /* bind the socket */
    rc = bind(listen_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (rc < 0 ) {
        perror("fail in bind()");
        close(listen_fd);
        exit(-1);
    }

    /* listen */
    rc = listen(listen_fd, backlog);
    if (rc < 0 ) {
        perror("fain in listen()");
        close(listen_fd);
        exit(-1);
    }
    
    curr_fd_num ++;
    printf("start listen!\n");

    /* init pollfd structure */
    bzero(&fd_arr, sizeof(fd_arr));

    /* init listening socket */
    fd_arr[0].fd = listen_fd;
    fd_arr[0].events = POLLIN;
    
    /* set timeout */
    timeout = 3*60*1000;

    conn_t* conn;
    /* poll loop */
    do {
        printf("start poll(), curr_fd_num = %d\n", curr_fd_num);
        rc = poll(fd_arr, MAX_FD_NUM, timeout);
        if (errno == EINTR) {
            // poll() may be interrupted by signal, if so, just ignore the fail and continue
            errno = 0;  // need to reset errno, or it will enter a infinite loop
            continue;
        }

        if (rc < 0) {      
            perror("fail in poll()");
            break;

        } else if (rc == 0) {
            // poll() timeout
            break;
        }

        for (int i=0; i<curr_fd_num; i++) {
        
            /* check */
            if (fd_arr[i].revents == 0) {
                continue;
            }

            if (fd_arr[i].revents != POLLIN) {
                printf("error! revent = %d\n", fd_arr[i].revents);
                end_server = 1;
                break;
            }
            /* end of check*/

            bzero(send_buff, BUFF_SIZE);

            if ((fd_arr[i].revents & POLLRDHUP) || (fd_arr[i].revents & POLLERR)) {
                // error or client close
                if (close(this_fd) < 0 ) {
                    perror("fail on close fd");
                    exit(-1);
                }

                // find fd from the tail and swap
                fd_arr[i].fd = -1;
                for (int j = curr_fd_num-1; j>0; j--) {
                    if (fd_arr[j].fd != -1) {
                        fd_arr[i] = fd_arr[j];
                        fd_arr[j].fd = 0;
                    }
                }
                curr_fd_num --;

                rc = table_remove(this_fd, table, conn_get_next, conn_match, conn_link);
                if (rc != 0) {
                    printf("error in table_remove()");
                    exit(1);
                }

            } else if ((fd_arr[i].fd == listen_fd) && (fd_arr[i].revents & POLLIN)) {
                // new client
                printf("listening socket is readable\n");

                this_fd = accept(listen_fd, NULL, NULL);
                if (this_fd < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("accept() failed");
                        end_server = 1;
                        break;
                    }
                }
                printf(" New incoming connection - %d\n", this_fd);
                curr_fd_num ++;
                fd_arr[curr_fd_num-1].fd = this_fd;
                fd_arr[curr_fd_num-1].events = POLLIN;

                conn = init_conn(this_fd);
                if (!conn) {
                    perror("fail in malloc for conn");
                    continue;
                }

                table_add(this_fd, table, (void*)conn, (void**)conn->next);

                snprintf(send_buff, BUFF_SIZE, "Enter your name: ");
                rc = send(this_fd, send_buff, BUFF_SIZE, 0);
                if (rc < 0) {
                    perror("fail in send()");
                    close_conn = 1;
                }

            
            } else if (fd_arr[i].revents & POLLIN) {
                // readable
 
                rc = recv(fd_arr[i].fd, rece_buff, BUFF_SIZE-1, 0);
                if (rc > 0)
                {
                    //mapdata[fds[i].fd] = buf;
                    fd_arr[i].events &= (~POLLIN);
                    fd_arr[i].events |= POLLOUT;
                }
                else if (rc == 0)
                {
                    printf("------- client %d exit (not print) --------\n", fd_arr[i].fd);
                }
                else
                {
                    fprintf(stderr, "recv: %d, %s\n", errno, strerror(errno));
                    exit(1);
                }
            
            } else if  (fd_arr[i].revents & POLLOUT) {
                // writable
				/*
				if (send(fd_arr[i].fd, mapdata[fds[i].fd].c_str(), mapdata[fds[i].fd].size(), 0) < 0)
                {
                    if (ECONNRESET == errno)
                    {
                        continue;
                    }
                    fprintf(stderr, "send: %d, %s\n", errno, strerror(errno));
                    exit(1);
                }
				*/
				printf("writable\n");
                fd_arr[i].events &= (~POLLOUT);
                fd_arr[i].events |= POLLIN;
            }
        } // for iterate all fd
    } while (end_server == 0);
}
