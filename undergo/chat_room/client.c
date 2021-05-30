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

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define BUFF_SIZE   100

char client_ip[12];
unsigned short client_port;

void sig_handler(int sig)
{
}


int main (int argc, char **argv)
{
    int rc;
    int client_fd = -1;
    int end_client = 0;
    struct sockaddr_in client_addr;
    char send_buff[BUFF_SIZE];
    char rece_buff[BUFF_SIZE];
    int rece_len;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        perror("fail to create client fd");
        exit(-1);
    }


    bzero(&client_addr, sizeof(client_addr));
    inet_pton(AF_INET, SERVER_IP, &(client_addr.sin_addr.s_addr));
    client_addr.sin_port = htons(SERVER_PORT);


    rc = connect(client_fd, (struct sockaddr*) &client_addr, sizeof(client_addr));
    if (rc < 0) {
        perror("fail to connect");
        exit(-1);
    }
    printf("connect\n");

    strcpy(send_buff, "hello");
    rc = send(client_fd, send_buff, BUFF_SIZE, 0);
    if (rc < 0) {
        perror("fail to send");
        goto done;
    }

    do {
    
        rc = recv(client_fd, rece_buff, BUFF_SIZE, 0);
        if (rc < 0) {
            perror("fail to receive");
            break;
        }

        printf("%s\n", rece_buff);
        //scanf("%[^\n]", send_buff);
        break;

    } while (!end_client);
    
done:
    close(client_fd);
}
