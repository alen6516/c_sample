#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>         // access()
#include <assert.h>
#include <pthread.h>


#include <sys/socket.h>     /* socket(), bind(), listen(), ... */
#include <netinet/in.h>     /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>      /* hton(), inet_ntop() */
#include <unistd.h>         /* read(), write(), close() */


#define DEBUG_MODE 1
#define INFO_MODE 0
#define ERROR_MODE 1
#define FAIL 1
#define SUCC 0

#define SERVER_IP "127.0.0.1"
#define PORT 8787
#define RECE_BUF_SIZE 1024
#define REPLY_BUF_SIZE 1024*2
#define BACKLOG 10          // backlog argument for listen()
#define ROOT_DIR "./www"
#define INDEX_PAGE "index.html"


#include "util.h"
#include "func.h"



void *rece_http (void *_fd) {

    int fd = *(int*)_fd;
    DEBUG("receive a client, fd = %d\n", fd);


    static char rece_buf[RECE_BUF_SIZE];
    bzero(rece_buf, RECE_BUF_SIZE);

    struct parse_buf_t parse_buf;
    bzero((void*) &parse_buf, sizeof(parse_buf));

    static char reply_buf[REPLY_BUF_SIZE];
    bzero(reply_buf, REPLY_BUF_SIZE);
    
    read(fd, rece_buf, RECE_BUF_SIZE);
    //DEBUG("%s", buf);
    

    if (SUCC != parse_http(rece_buf, reply_buf, &parse_buf)) {
        return NULL;
    }
    DEBUG("\n");
  

    /* Resetting a TCP connection by setting SO_LINGER */
    struct linger s1;
    s1.l_onoff = 1;
    s1.l_linger = 0;
    setsockopt(fd, SOL_SOCKET, SO_LINGER, &s1, sizeof(s1));

    close(fd);
    pthread_exit(SUCC);
}


int parse_http (char* rece_buf, char* reply_buf, struct parse_buf_t* parse_buf) {
    #define CRLF "\r\n"
    
    
    //DEBUG("in parse_http\n");


    int start_idx = 0;
    int data_len = strlen(rece_buf);


    bool if_fail = SUCC;


    // split http
    for (int i=0; i<data_len; i++) {
    
        if (i+1 <= data_len && rece_buf[i] == '\r' && rece_buf[i+1] == '\n') {
            if (i == data_len -2 && i == start_idx) {
                // end of http
                DEBUG("reach the end of http\n");
                
            } else {

                if (start_idx == 0) {
                    // parse http method

                    if_fail = parse_http_method(rece_buf, i-start_idx, parse_buf);

                    if (if_fail) {
                        return FAIL;
                    }

                } else {
                    // parse Host, User-Agent, ...
                    
                    if_fail = _parse_http(rece_buf + start_idx, i-start_idx, parse_buf);
                    
                    if (if_fail) {
                        return FAIL;
                    }
                }
                
                start_idx = i+2;
            }
        }
    }

    if_fail = reply_http(reply_buf, parse_buf);
    if (if_fail) {
        return FAIL;
    }

    return SUCC;
}


int _parse_http (char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {
    
    //DEBUG("in _parse_http\n");


    /*
     *  parse_buf->parse_bit_map:
     *
     *  0: method
     *  1: HOST
     *  2: User-Agent
     *  3: Accept
     *  4:
     *  5:
     *  6:
     *  7:
     */


    bool if_fail = SUCC;

    // parse HOST, user-agent, accept, ...
    if (0 == strncmp(rece_buf, "Host:", 5)) {
        DEBUG("HOST get\n");
        parse_buf->parse_bit_map |= B_HOST;

        if_fail = parse_host(rece_buf, data_len, parse_buf);


    } else if (0 == strncmp(rece_buf, "User-Agent:", 11)) {
        DEBUG("User-Agent get\n");
        parse_buf->parse_bit_map |= B_USER_AGENT;

    } else if (0 == strncmp(rece_buf, "Accept:", 7)) {
        DEBUG("Accept get\n");
        parse_buf->parse_bit_map |= B_ACCEPT;

    } else {
        DEBUG("UNKNOW-->");
        for (int i=0; i<data_len; i++) {
            DEBUG("%c", rece_buf[i]);
        }
        DEBUG("\n");
    }


    return SUCC;

}


int parse_http_method(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {



    /*  parse_buf->method_bit_map:
     *
     *  0: GET
     *  1: POST
     *  2: HEAD
     *  3: PUT
     *  4: DELETE
     *  5: TRACE
     *  6: CONNECT
     *  7: OPTIONS
     */


    bool if_fail = SUCC;

    // parse method
    if (0 == strncmp(rece_buf, GET_PRE_STR, GET_PRE_LEN)) {

        DEBUG("method GET\n");

        // paesr file name
        rece_buf += GET_PRE_LEN;
        if_fail = parse_file_name(rece_buf, data_len, parse_buf);
        if (if_fail) {
            return FAIL;
        }


        // parse version
        rece_buf += (strlen(parse_buf->file_name)+1);
        if_fail = parse_http_version(rece_buf, data_len, parse_buf)
        if (if_fail) {
            return FAIL;
        }

        parse_buf->method_bit_map |= B_GET;
        
    } else if (0 == strncmp(rece_buf, HEAD_PRE_STR, HEAD_PRE_LEN)) {

        DEBUG("method HEAD\n");
        parse_buf->method_bit_map |= B_HEAD;
        
    } else if (0 == strncmp(rece_buf, POST_PRE_STR, POST_PRE_LEN)) {

        DEBUG("method POST\n");
        parse_buf->method_bit_map |= B_POST;
    
    } else if (0 == strncmp(rece_buf, PUT_PRE_STR, PUT_PRE_LEN)) {

        DEBUG("method PUT\n");
        parse_buf->method_bit_map |= B_PUT;
    
    } else if (0 == strncmp(rece_buf, DELETE_PRE_STR, DELETE_PRE_LEN)) {

        DEBUG("method DELETE\n");
        parse_buf->method_bit_map |= B_DELETE;
    
    } else {

        DEBUG("parse method fail, unknown method\n");
        return FAIL;
    }


    // after parsing, bit should be turned on
    assert( (parse_buf->parse_bit_map & B_METHOD) == 0);
    parse_buf->parse_bit_map |= B_METHOD;

    assert(parse_buf->method_bit_map != 0);
    return SUCC;
}


int parse_file_name(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {


    // debug
    DEBUG("\t");
    for (int i=0; i<data_len; i++) {
        DEBUG("%c", rece_buf[i]);
    }
    DEBUG("\n");
    // end of debug


    
    int file_len = 0;
    char *file_name;

    // parse file name length
    while (rece_buf[file_len] != ' ') {
        file_len ++;
    }
    DEBUG("file len = %d\n", file_len);
  

    // file name
    file_name = (char*) malloc(sizeof(char)*(file_len+1));
    if (NULL == file_name) {
        ERROR("Can't malloc for file name\n");
        return FAIL;
    }
    strncpy(file_name, rece_buf, file_len);
    DEBUG("file name = %s\n", file_name);


    // handle filename = /    
    if (0 == strcmp(file_name, "/")) {
        
        file_name = (char*) realloc(file_name, strlen(INDEX_PAGE)+1);
        if (NULL == file_name) {
            ERROR("Can't realloc for file name\n");
            return FAIL;
        }
        strcpy(file_name, INDEX_PAGE);
        DEBUG("after realloc, file name = %s\n", file_name);
    } 

    
    if ( -1 != access(file_name, F_OK) ) {
        // can not find file
        ERROR("Access file fail\n");
        parse_buf->reply_status = CODE_404;
        
    } else {
        // find the file
        DEBUG("find file %s\n", file_name);
        parse_buf->file_name = file_name;
        parse_buf->reply_status = CODE_200;
    }


    //free(file_name);
    return SUCC;

}


int parse_http_version(char* rece_buf, int data_len, struct parse_buf_t* parse_buf) {


    if (0 == strncmp(rece_buf, "HTTP/1.0", VERSION_10_len)) {

        DEBUG("http version 1.0\n");
        parse_buf->version = e_http_10;

    } else if (0 == strncmp(rece_buf, "HTTP/1.0", VERSION_11_len)) {

        DEBUG("http version 1.1\n");
        parse_buf->version = e_http_11;

    }

    return SUCC;
}

int parse_host(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {


    DEBUG("\t");
    for (int i=0; i<data_len; i++) {
        DEBUG("%c", rece_buf[i]);
    }
    DEBUG("\n");
    return SUCC;

}


int reply_http(char* reply_buf, struct parse_buf_t* parse_buf) {
    
    DEBUG("in reply_http\n");

    return SUCC;

    // paste http version
    switch (parse_buf->http_version) {
        case e_http_10:
            strncat(reply_buf, VERSION_10_STR, VERSION_10_len);
            break;

        case e_http_11:
            strncat(reply_buf, VERSION_11_STR, VERSION_11_len);
            break;

        case e_http_12:
            strncat(reply_buf, VERSION_12_STR, VERSION_12_len);
            break;
    
    }
    strncat(reply_buf, " ", 1);     // need a space
    
    
    // paste status code
    switch (parse_buf->reply_status) {
        case CODE_200:
            strncpy(reply_buf, CODE_200_STR, CODE_200_len);
            reply_buf += CODE_200_len;
            break;
    }

}


int main (int argc, char *argv[]) {


    // cd to root dir
    if ( -1 == chdir(ROOT_DIR) ) { 
        perror("Can't Change to directory");
        exit(4);
    }


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
    //serv_addr.sin_addr.s_addr = htonl(0x7f000001);
    inet_pton(AF_INET, SERVER_IP, &(serv_addr.sin_addr.s_addr));
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
