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

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define BACKLOG 128


char server_ip[12];
unsigned short server_port;
int backlog;
struct pollfd fd_arr[200];
int fd_num = 1;


table_t *table;


void sig_hander(int sig) {

    printf("\n================================\n");
    printf("fd_num = %d, fd_arr = [ ", fd_num);
    for (int i=0; i<fd_num; i++) {
        printf("%d ", fd_arr[i].fd);
    }
    printf("]\n");
    printf("================================\n");
}


int main (int argc, char *argv[]) {

    table = init_table();
    if (!table) {
        printf("fail in malloc for table\n");
        exit(1);
    }

    int rc;  
    int on = 1;
    int listen_fd = -1, new_fd = -1;
    struct sockaddr_in serv_addr;
    int timeout;
    int curr_fd_num;

    char buff[100];
    int rece_len;

    int end_server = 0, compress_array = 0;
    int close_conn;


    strcpy(server_ip, SERVER_IP);
    server_port = (unsigned short)SERVER_PORT;
    backlog = BACKLOG;

    signal(SIGTSTP, sig_hander);

    /* create listen_fd */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("fail in creating listen_fd");
        exit(-1);
    }


    /* set socket reuse */
    rc = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, 
        (char*) &on, sizeof(on));
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

    /* bind the socket */
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &(serv_addr.sin_addr.s_addr));
    serv_addr.sin_port = htons(9000);
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
    
    printf("start listen!\n");

    /* init pollfd structure */
    bzero(&fd_arr, sizeof(fd_arr));

    /* setup init listening socket */
    fd_arr[0].fd = listen_fd;
    fd_arr[0].events = POLLIN;
    
    /* set timeout */
    timeout = 3*60*1000;

    conn_t* conn;

    do {
        printf("start poll(), fd_num = %d\n", fd_num);
        rc = poll(fd_arr, fd_num, timeout);
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

        // if rc > 0
        curr_fd_num = fd_num;
        for (int i=0; i<curr_fd_num; i++) {
        
            if (fd_arr[i].revents == 0) {
                continue;
            }

            if (fd_arr[i].revents != POLLIN) {
                printf("error! revent = %d\n", fd_arr[i].revents);
                end_server = 1;
                break;
            }

            if (fd_arr[i].fd == listen_fd) {
                printf("listening socket is readable\n");

                new_fd = accept(listen_fd, NULL, NULL);
                if (new_fd < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("accept() failed");
                        end_server = 1;
                        break;
                    }
                }
                printf(" New incoming connection - %d\n", new_fd);
                fd_arr[fd_num].fd = new_fd;
                fd_arr[fd_num].events = POLLIN;
                fd_num ++;

                conn = init_conn(new_fd);
                if (!conn) {
                    perror("fail in malloc for conn");
                    continue;
                }

                table_add(conn->fd, table, (void*)conn, (void**)conn->next);

            } else {
                printf("fd %d is readable\n", fd_arr[i].fd);
                close_conn = 0;
                
                rc = recv(fd_arr[i].fd, buff, sizeof(buff), 0);
                if (rc < 0) {
                    if (errno != EWOULDBLOCK) {
                        close_conn = 1;
                    }
                    break;
                }

                if (rc == 0) {
                    printf("Connection closed\n");
                    close_conn = 1;
                }

                rece_len = rc;
                printf("%d bytes received\n", rece_len);

                rc = send(fd_arr[i].fd, buff, rece_len, 0);
                if (rc < 0) {
                    perror("fail in send()");
                    close_conn = 1;
                }

                if (close_conn) {
                    close(fd_arr[i].fd);
                    fd_arr[i].fd = -1;
                    compress_array = 1;

                    rc = table_remove(fd_arr[i].fd, table, conn_iter, conn_match, conn_link);
                    if (rc != 0) {
                        printf("error in table_remove()");
                        exit(1);
                    }
                } 
            }
        } // for iterate all fd
        if (compress_array) {
            printf("in compress\n");
            compress_array = 0;
            for (int i=0; i<fd_num; i++) {
                if (fd_arr[i].fd == -1) {
                    for (int j=fd_num-1; j>=i; j--) {
                        fd_num --;
                        if (fd_arr[j].fd != -1) {
                            fd_arr[i].fd = fd_arr[j].fd;
                            break;
                        }
                    }
                }
            }
        }
    } while (end_server == 0);

    for (int i=0; i<fd_num; i++) {
        if (fd_arr[i].fd == 0) {
            close(fd_arr[i].fd);
        }
    }
}
