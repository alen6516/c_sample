#include <stdlib.h>   
#include <stdio.h>   
#include <stddef.h>   
#include <sys/socket.h>   
#include <sys/un.h>   
#include <errno.h>   
#include <string.h>   
#include <unistd.h>   
#include <ctype.h>   
 
#define MAXLINE 80  
 
const char *socket_path = "server.socket";  
 
int main( void )  
{  
    struct sockaddr_un ser_un, cli_un;  
    socklen_t cli_un_len;  
    int listen_fd, conn_fd, size;  
    char buf[MAXLINE];  
    int i, n;  
 
    if ((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0 )) < 0 ) {  
        perror( " socket error " );  
        exit( 1 );  
    }  
 
    memset( &ser_un, 0 , sizeof (ser_un));  
    ser_un.sun_family = AF_UNIX;  
    strcpy(ser_un.sun_path, socket_path);  
    size = offsetof( struct sockaddr_un, sun_path) + strlen(ser_un.sun_path);  
    unlink(socket_path);  
    if (bind(listen_fd, ( struct sockaddr *)&ser_un, size) < 0 ) {  
        perror( " bind error " );  
        exit( 1 );  
    }  
    printf( " UNIX domain socket bound\n " );  
      
    if (listen(listen_fd, 20 ) < 0 ) {  
        perror( " listen error " );  
        exit( 1 );          
    }  
    printf( " Accepting connections ...\n " );  
 
    while ( 1 ) {  
        cli_un_len = sizeof (cli_un);         
        if ((conn_fd = accept(listen_fd, ( struct sockaddr *)&cli_un, &cli_un_len)) < 0 ){  
            perror( " accept error " );  
            continue ;  
        }  
          
        while ( 1 ) {  
            n = read(conn_fd, buf, sizeof (buf));  
             if (n < 0 ) {  
                perror( " read error " );  
                break ;  
            } else  if (n == 0 ) {  
                printf( " EOF\n " );  
                break ;  
            }  
              
            printf( " received: %s " , buf);  
 
            for (i = 0 ; i < n; i++ ) {  
                buf[i] = toupper(buf[i]);  
            }  
            write(conn_fd, buf, n);  
        }  
        close(conn_fd);  
    }  
    close(listen_fd);  
    return  0 ;  
} 
