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

#include "table.h"
#include "conn.h"
#include "util.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_FD_NUM  200
#define BACKLOG     128
#define BUF_SIZE    100

#ifdef DEBUG
#define LOG(...) ({             \
        printf(__VA_ARGS__);    \
})
#else
#define LOG(...)
#endif


int main ()
{
    
    int rc;
    int listen_fd = -1;
    struct sockaddr_in  serv_addr;

    // create server socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        // fail
        exit(-1);
    }

    // set server socket reuse
    int socket_flag = 1;
    rc = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&socket_flag, sizeof(socket_flag));
    if (rc < 0) {
        // fail
        exit(-1);
    }

    // config & bind the socket
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERVER_PORT);
    rc = bind(listen_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (rc < 0) {
        exit(-1);
    }

    // listen
    rc = listen(listen_fd, BACKLOG);
    if (rc < 0) {
        close(listen_fd);
        exit(-1);
    }

    // setup fd_set
    fd_set active_fd_set;
    FD_ZERO(&active_fd_set);
    FD_SET(listen_fd, &active_fd_set);
    int max_fd = listen_fd;


    // main loop
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    fd_set read_fds;
    struct sockaddr_in cli_addr;
    int new_fd;
    char recv_buf[BUF_SIZE] = {};
    int recv_len;
    while (1) {
        
        // copy fd_set
        read_fds = active_fd_set;
        rc = select(max_fd+1, &read_fds, NULL, NULL, &tv);
        if (rc == -1) {
            // select fail
        } else if (rc == 0) {
            // select timeout
        } else {
            
            // serve all sockets
            for (int i=0; i<FD_SETSIZE; i++) {
                if (FD_ISSET(i, &read_fds)) {
                    if (i == listen_fd) {
                        // new conn
                        
                        new_fd = accept(listen_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr));
                        if (new_fd == -1) {
                            // fail to accept
                            
                        } else {
                            LOG("Accpet client come from [%s:%u] by fd [%d]\n",
                                inet_ntoa(cli_addr.sin_addr),
                                ntohs(cli_addr.sin_port), new_fd);

                            // add to fd_set
                            FD_SET(new_fd, &active_fd_set);
                            if (new_fd > max_fd) {
                                max_fd = new_fd;
                            }
                        }
                    } else {
                        // data to existing socket
                        recv_len = recv(i, recv_buf, BUF_SIZE, 0);
                        if (recv_len == -1) {
                            // fail to recv
                        } else if (recv_len == 0) {
                            LOG("client disconnected\n");
                        } else {
                            LOG("Receive: len=[%d] msg=[%s]\n", recv_len, recv_buf);
                            /* Send (In fact we should determine when it can be written)*/
                            send(i, recv_buf, recv_len, 0);
                        }

                        /* Clean up */
                        close(i);
                        FD_CLR(i, &active_fd_set);
                    }
                }
            } // end of iter all fd
        }
    } // end of main while

}
