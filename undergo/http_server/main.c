#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#include <sys/socket.h>     /* socket(), bind(), listen(), ... */
#include <netinet/in.h>     /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>      /* hton */
#include <unistd.h>         /* read(), write(), close() */


#define DEBUG_MODE 1
#include "util.h"
#include "func.h"


#define PORT 8787
#define BUF_SIZE 1024*2
#define BACKLOG 10          // backlog argument for listen()


void *rece_http(void *_fd) {

    int fd = *(int*)_fd;
    DEBUG("receive a client, fd = %d\n", fd);
    char buf[BUF_SIZE];
    bzero(buf, BUF_SIZE);
    
    read(fd, buf, BUF_SIZE);
    DEBUG("%s", buf);

    if (0 != parse_http(buf)) {
        DEBUG("fail in parse http\n");
    }

    close(fd);
    pthread_exit(NULL);
}


int parse_http(char* data) {
    #define CRLF "\r\n"
    
    //struct http_hdr_t* http_hdr;
    

    // debug
    
    if (data[0] == '\r')
        printf("gg\n");
    else
        printf("123");
    
    for (int i=0; data[i] != '\0'; i++) {
        if (data[i] == '\r')
            printf("CR");
        else if (data[i] == '\n')
            printf("LF");
        else
            printf("%c", data[i]);
    }


    return 0;
}


int main (int argc, char *argv[]) {

    int listenfd;
    static struct sockaddr_in serv_addr;

    int socketfd;                           // for accept
    static struct sockaddr_in cli_addr;     // for accept
    socklen_t addr_len;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // why status is 3?
        exit(3);
    }

   
    // Setup server addr
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);


    // bind
    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }


    // listen
    if (listen(listenfd, BACKLOG) < 0) {
        perror("listen failed");
        exit(1);
    }

    DEBUG("start listen\n");

    while (1) {
        addr_len = sizeof(cli_addr);

        if ((socketfd = accept(listenfd, (struct sockaddr *) &cli_addr, &addr_len)) < 0) {
            perror("accept fail");
            exit(1);
        } 
       

        pthread_t work_thr;
        pthread_create(&work_thr, NULL, rece_http, (void*) &socketfd);
    }
}
