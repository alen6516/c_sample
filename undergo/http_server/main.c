#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#include <sys/socket.h>     /* socket(), bind(), listen(), ... */
#include <netinet/in.h>     /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>      /* hton */

void handle_socket(int fd) {


}

int main (int argc, char *argv[]) {

    int listenfd, socketfd;
    static struct sockaddr_in cli_addr;
    static struct sockaddr_in serv_addr;
    socklen_t addr_len;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // why status is 3?
        exit(3);
    }

   
    // network configuration
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(80);

    // bind
    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        exit(3);
    }

    // listen
    if (listen(listenfd, 64) < 0) {
        exit(3);
    }


    while (1) {
        addr_len = sizeof(cli_addr);

        if ((socketfd = accept(listenfd, (struct sockaddr *) &cli_addr, &addr_len)) < 0) {
            exit(3);
        } 
       

        pthread_t work_thr;
        pthread_create(&work_thr, NULL, handle_socket, socketfd);
    }
}
