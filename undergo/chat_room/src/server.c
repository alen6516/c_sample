
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

#include "client_table.h"
#include "util.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_FD_NUM  200
#define BACKLOG     128
#define BUFF_SIZE    100

int
broadcast(int fd, char *recv_buff, u32 recv_len)
{
    u32 bucket;
    cli_conn_t *cli_conn;
    char send_buff[BUFF_SIZE];

    cli_conn = client_conn_lookup(fd);
    if (!cli_conn) {
        cli_conn = (cli_conn_t*) malloc(sizeof(cli_conn_t));
        if (!cli_conn) {
            ERROR("out of memory\n");
            exit(-1);
        }
        memset(cli_conn, 0, sizeof(cli_conn));
        cli_conn->key = fd;
        strncpy(cli_conn->name, recv_buff, 10);
        client_conn_insert(cli_conn);
        snprintf(send_buff, BUFF_SIZE, "let's welcome %s!", cli_conn->name);

    } else {
        if (!recv_len) {
            snprintf(send_buff, BUFF_SIZE, "%s leaves...", cli_conn->name);
        } else {
            snprintf(send_buff, BUFF_SIZE, "%s says: %s", cli_conn->name, recv_buff);
        }
    }
    printf("%s\n", send_buff);


    /* broadcast */
    cli_conn_t *curr;
    for (u32 curr_bucket = 0; curr_bucket < CLIENT_TABLE_BUCKET_SIZE; curr_bucket++) {
        curr = cli_conn_bucket[curr_bucket];
        while (curr && curr->fd != fd) {
            send(curr->fd, send_buff, BUFF_SIZE, 0);
            curr = curr->next;
        }
    }
}

int
main(int argc, char *argv[])
{
    int ret;
    int listen_fd = -1;
    struct sockaddr_in  serv_addr;

    /* create server socket */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        ERROR("servr create socket fail\n");
        exit(-1);
    }
    INFO("server create socket\n");

    /* set server socket reuse */
    int socket_flag = 1;
    ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&socket_flag, sizeof(socket_flag));
    if (ret < 0) {
        ERROR("server set socekt fail\n");
        exit(-1);
    }
    INFO("server set socket\n");

    /* config & bind the socket */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERVER_PORT);
    ret = bind(listen_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        ERROR("server bind socket fail\n");
        exit(-1);
    }
    INFO("server bind socket\n");

    /* listen */
    ret = listen(listen_fd, BACKLOG);
    if (ret < 0) {
        ERROR("server listen fail\n");
        close(listen_fd);
        exit(-1);
    }
    INFO("server listen\n");

    /* init the set of active socket */
    fd_set active_fd_set, read_fd_set;
    FD_ZERO(&active_fd_set);
    FD_SET(listen_fd, &active_fd_set);
    int max_fd = listen_fd;


    //struct timeval tv;
    //tv.tv_sec = 2;
    //tv.tv_usec = 0;
    //fd_set read_fds;
    struct sockaddr_in cli_addr;
    socklen_t *addr_len;
    int new_fd;
    char recv_buff[BUFF_SIZE] = {0};
    char send_buff[BUFF_SIZE] = {0};
    int recv_len, send_len;
    u8 is_client_close = 0;
    cli_conn_t* cli_conn;

    while (1) {

        // block until input arrives on one or more active sockets
        read_fd_set = active_fd_set;
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
            ERROR("server select fail\n");
            exit(-1);
        }

        // iterate all sockets
        for (int i=0; i<=max_fd; i++) {
            if (FD_ISSET(i, &read_fd_set)) {
                if (i == listen_fd) {
                    /* new client */
                    new_fd = accept(listen_fd, (struct sockaddr*) &cli_addr, &recv_len);
                    if (new_fd < 0) {
                        ERROR("fail to accept\n");
                    }

                    printf("Accept client come from [%s:%u] by fd [%d]\n",
                        inet_ntoa(cli_addr.sin_addr),
                        ntohs(cli_addr.sin_port), new_fd);

                    // add to fd_set
                    FD_SET(new_fd, &active_fd_set);
                    if (new_fd > max_fd) {
                        max_fd = new_fd;
                    }

                    snprintf(send_buff, BUFF_SIZE, "Hello client, what's your name?");
                    send_len = send(new_fd, send_buff, BUFF_SIZE, 0);

                } else {
                    /* existing client */
                    recv_len = recv(i, recv_buff, BUFF_SIZE, 0);
                    if (recv_len == -1) {
                        // fail to recv
                        printf("fail to receive msg from a existing client\n");
                        is_client_close = 1;
                    } else {
                        if (recv_len == 0) {
                            printf("client disconnected\n");
                            is_client_close = 1;
                        } else {
                            printf("Receive: len=[%d] msg=[%s]\n", recv_len, recv_buff);
                        }
                        /* Send (In fact we should determine when it can be written)*/
                        
                        broadcast(i, recv_buff, recv_len);
                    }

                    /* Clean up */
                    if (is_client_close) {
                        close(i);
                        FD_CLR(i, &active_fd_set);
                        cli_conn = client_conn_remove(i);
                        if (cli_conn) {
                            free(cli_conn);
                        }
                        is_client_close = 0;
                    }
                }
            }
        }
    }
}
