#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <time.h>

#define SERV_PORT 8000

#define MAXNAME 1024

extern int errno;

void thread(int *count) {
    
    int old_count = 0;
    while (1) {
        sleep(1);
        printf("count = %d\n", (*count) - old_count);
        old_count = *count;
    }
}

int main() {
    int socket_fd;      /* file description into transport  */
    int recfd;          /* file descriptor to accept        */
    int length;         /* length of address structure      */
    int nbytes;         /* the number of read */
    char buf[BUFSIZ];
    struct sockaddr_in myaddr;      /* address of this service  */
    struct sockaddr_in client_addr; /* address of client        */
    /*
     * Get a socket into UDP/IP
     */
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) <0) {
        perror ("socket failed");
        exit(EXIT_FAILURE);
    }
    /*
     * Set up our address
     */
    bzero ((char *)&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(SERV_PORT);

    /*
     * Bind to the address to which the service will be offered
     */
    if (bind(socket_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) <0) {
        perror ("bind failed\n");
        exit(1);
    }

    /*
     * Loop continuously, waiting for datagrams
     * and response a message
     */
    length = sizeof(client_addr);
    printf("Server is ready to receive !!\n");
    printf("Can strike Cntrl-c to stop Server >>\n");

    
    int count = 0;
    
    pthread_t id;
    int i,ret;
    ret = pthread_create(&id, NULL, (void *) thread, (void*) &count);
    if(ret != 0){
        printf ("Create pthread error!n");
        exit (1);
    }

    while (1) {
        if ((nbytes = recv(socket_fd, &buf, MAXNAME, 0)) <0) {
            perror ("could not read datagram!!");
            continue;
        }

        
        count++;

        //printf("Received data form %s : %d\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));
        //printf("%s\n", buf);

        /* return to client */
        //if (sendto(socket_fd, &buf, nbytes, 0, (struct sockaddr*)&client_addr, length) < 0) {
        //      perror("Could not send datagram!!\n");
        //      continue;
        //}
        //printf("Can Strike Crtl-c to stop Server >>\n");
    }
}
