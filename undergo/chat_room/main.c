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


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8787
#define BACKLOG 128

char server_ip[12];
unsigned char server_port;
int backlog;

int main (int argc, char *argv[]) {

    int rc;  
    int on = 1;
    int listen_fd = -1, new_fd = -1;
    struct sockaddr_in serv_addr;
    int timeout;
    struct pollfd fd_arr[200];
    int fd_num = 1;
    int curr_fd_num;

    strcpy(server_ip, SERVER_IP);
    server_port = (unsigned char)SERVER_PORT;
    backlog = BACKLOG;


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
    serv_addr.sin_port = htons(server_port);
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

    /* init pollfd structure */
    bzero(&fd_arr, sizeof(fd_arr));

    /* setup init listening socket */
    fd_arr[0].fd = listen_fd;
    fd_arr[0].events = POLLIN;
    
    /* set timeout */
    timeout = 3*60*1000;

    while (1) {
        rc = poll(fd_arr, fd_num, timeout);
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


        
        
        }


        
    }
}
