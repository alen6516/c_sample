#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define SVR_IP 		"127.0.0.1"
#define SVR_PORT    8080
#define BUF_SIZE    1024
 
int main (int argc, char **argv) {
    struct sockaddr_in  server_addr;
    socklen_t           len;
    fd_set              active_fd_set;
    int                 sock_fd;
    int                 max_fd;
    int                 flag = 1;
    char                buff[BUF_SIZE];
     
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SVR_IP);
    server_addr.sin_port = htons(SVR_PORT);
    len = sizeof(struct sockaddr_in);
 
    /* Create endpoint */
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        return -1;
    } else {
        printf("sock_fd=[%d]\n", sock_fd);
    }
 
    /* Set socket option */
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
        perror("setsockopt()");
        return -1;
    }
 
    /* Bind */
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind()");
        return -1;
    } else {
        printf("bind [%s:%u] success\n",
            inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    }
 
    /* Listen */
    if (listen(sock_fd, 128) == -1) {
        perror("listen()");
        return -1;
    }
 
    FD_ZERO(&active_fd_set);
    FD_SET(sock_fd, &active_fd_set);
    max_fd = sock_fd;
 
    while (1) {
        int             ret;
        struct timeval  tv;
        fd_set          read_fds;
 
        /* Set timeout */
        tv.tv_sec = 2;
        tv.tv_usec = 0;
 
        /* Copy fd set */
        read_fds = active_fd_set;
        ret = select(max_fd + 1, &read_fds, NULL, NULL, &tv);
        if (ret == -1) {
            perror("select()");
            return -1;
        } else if (ret == 0) {
            printf("select timeout\n");
            continue;
        } else {
            int i;
 
            /* Service all sockets */
            for (i = 0; i < FD_SETSIZE; i++) {
                if (FD_ISSET(i, &read_fds)) {
                    if (i == sock_fd) {
                        /* Connection request on original socket. */
                        struct sockaddr_in  client_addr;
                        int                 new_fd;
 
                        /* Accept */
                        new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &len);
                        if (new_fd == -1) {
                            perror("accept()");
                            return -1;
                        } else {
                            printf("Accpet client come from [%s:%u] by fd [%d]\n",
                                inet_ntoa(client_addr.sin_addr),
                                ntohs(client_addr.sin_port), new_fd);
 
                            /* Add to fd set */
                            FD_SET(new_fd, &active_fd_set);
                            if (new_fd > max_fd)
                                max_fd = new_fd;
                        }
                    } else {
                        /* Data arriving on an already-connected socket */
                        int recv_len;
 
                        /* Receive */
                        memset(buff, 0, sizeof(buff));
                        recv_len = recv(i, buff, sizeof(buff), 0);
                        if (recv_len == -1) {
                            perror("recv()");
                            return -1;
                        } else if (recv_len == 0) {
                            printf("Client disconnect\n");
                        } else {
                            printf("Receive: len=[%d] msg=[%s]\n", recv_len, buff);
 
                            /* Send (In fact we should determine when it can be written)*/
                            send(i, buff, recv_len, 0);
                        }
 
                        /* Clean up */
                        close(i);
                        FD_CLR(i, &active_fd_set);
                    }
 
                } // end of if
            } //end of for
        } // end of if
    } // end of while
     
    return 0;
}
