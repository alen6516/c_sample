#include <stdlib.h>   
#include <stdio.h>   
#include <stddef.h>   
#include <sys/socket.h>   
#include <sys/un.h>   
#include <errno.h>   
#include <string.h>   
#include <unistd.h>  
 
#define MAXLINE 80  
 
const char *client_path = "client.socket";  
const char *server_path = "server.socket";  
 
int main() {  
     struct   sockaddr_un cli_un, ser_un;  
     int len;  
     char buf[ 100 ];  
     int sockfd, n;  
 
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0 )) < 0 ){  
        perror( " client socket error " );  
        exit( 1 );  
    }  
      
    // 一般顯式調用bind函數，以便服務器區分不同客戶端   
    memset(&cli_un, 0 , sizeof (cli_un));  
    cli_un.sun_family = AF_UNIX;  
    strcpy(cli_un.sun_path, client_path);  
    len = offsetof( struct sockaddr_un, sun_path) + strlen(cli_un.sun_path);  
    unlink(cli_un.sun_path);  
    if (bind(sockfd, ( struct sockaddr *)&cli_un, len) < 0 ) {  
        perror( " bind error " );  
        exit( 1 );  
    }  
 
    memset( &ser_un, 0 , sizeof (ser_un));  
    ser_un.sun_family = AF_UNIX;  
    strcpy(ser_un.sun_path, server_path);  
    len = offsetof( struct sockaddr_un, sun_path) + strlen(ser_un.sun_path);  
     if (connect(sockfd, ( struct sockaddr *)&ser_un, len) < 0 ){  
        perror( " connect error " );  
        exit( 1 );  
    }  
 
    while (fgets(buf, MAXLINE, stdin) != NULL) {    
         write(sockfd, buf, strlen(buf));    
         n = read(sockfd, buf, MAXLINE);    
          if ( n < 0 ) {    
            printf( " the other side has been closed.\n " );    
         } else {    
            write(STDOUT_FILENO, buf, n);    
         }    
    }   
    close(sockfd);  
    return  0 ;  
}  
