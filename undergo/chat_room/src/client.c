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

//#include "table.h"
//#include "conn.h"
#include "util.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define BUFF_SIZE   100

char client_ip[12];
unsigned short client_port;


/**
 * Catch ctrl-z and print status.
 */
void
sig_handler(int sig)
{
}

void *
sender_thread(void *fd)
{
    INFO("sender_thread start\n");
    int rc = 0;
    char send_buff[BUFF_SIZE];
    while (1) {
        //scanf(" %[^\n]", send_buff);
        scanf("%s", send_buff);
        fflush(stdin);
        rc = send(*(int*)fd, send_buff, BUFF_SIZE, 0);
    }
}

int
main (int argc, char **argv)
{
    int rc;
    int client_fd = -1;
    int is_end_client = 0;  // global toggle to end the client
    struct sockaddr_in client_addr;

    /* create a socket */
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        ERROR("fail to create client fd");
        exit(-1);
    }
    INFO("create socket\n");

    /* config socket */
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &(client_addr.sin_addr.s_addr));
    client_addr.sin_port = htons(SERVER_PORT);

    /* connect */
    rc = connect(client_fd, (struct sockaddr*) &client_addr, sizeof(client_addr));
    if (rc < 0) {
        ERROR("fail to connect");
        exit(-1);
    }
    INFO("connect\n");

    pthread_t sender;
    pthread_create(&sender, NULL, sender_thread, (void*)&client_fd);
    
    char recv_buff[BUFF_SIZE];
    do {
        rc = recv(client_fd, recv_buff, BUFF_SIZE, 0);
        if (rc < 0 ) {
            ERROR("fail to receive");
        }
        printf("%s\n", recv_buff);
    } while (!is_end_client);

done:
    close(client_fd);
}
