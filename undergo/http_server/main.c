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
#define NOT_FOUND_PAGE "404_not_found.html"


#include "util.h"
#include "func.h"



void *rece_http (void *_fd) {

    int fd = *(int*)_fd;
    DEBUG("receive a client, fd = %d\n", fd);

    // init rece_buf
    static char rece_buf[RECE_BUF_SIZE];
    bzero(rece_buf, RECE_BUF_SIZE);

    // init parse_buf
    struct parse_buf_t parse_buf;
    bzero((void*) &parse_buf, sizeof(parse_buf));

    // init reply_buf
    static char reply_buf[REPLY_BUF_SIZE];
    bzero(reply_buf, REPLY_BUF_SIZE);
    

    parse_buf.fd = fd;
    

    read(fd, rece_buf, RECE_BUF_SIZE);
    DEBUG("rece_buf ===== \n%s=====\n", rece_buf);
    

    if (SUCC != parse_http(rece_buf, reply_buf, &parse_buf)) {
        // 
    }
    DEBUG("\n");
  

    /* Resetting a TCP connection by setting SO_LINGER */
    struct linger s1;
    s1.l_onoff = 1;
    s1.l_linger = 0;
    setsockopt(fd, SOL_SOCKET, SO_LINGER, &s1, sizeof(s1));

    close(fd);
    pthread_exit(SUCC);   // no need unlesss want to pass retval
}


int parse_http (char* rece_buf, char* reply_buf, struct parse_buf_t* parse_buf) {
    #define CRLF "\r\n"
    
    
    INFO("in parse_http\n");


    size_t start_idx = 0;
    size_t data_len = strlen(rece_buf);


    bool if_fail = SUCC;


    // split http
    for (size_t i=0; i<data_len; i++) {

        // if reach "/r/n"
        if (i+1 <= data_len && rece_buf[i] == '\r' && rece_buf[i+1] == '\n') {
            
            if (i == data_len -2 && i == start_idx) {
                // end of http
                DEBUG("reach the end of http\n");
                
            } else if (start_idx == 0) {
                // http startline
                parse_http_startline(rece_buf, i, parse_buf);

            } else {
                // http header ( Host, User-Agent, ...)
                parse_http_header(rece_buf + start_idx, i-start_idx, parse_buf);
            }
            start_idx = i+2;
        }
    }

    if ( (if_fail = reply_http(reply_buf, parse_buf)) ) {
        return FAIL;
    }

    return SUCC;
}


int parse_http_startline(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {



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


    // startlin is "GET / HTTP/1.1"
    if (IF_MATCH_GET(rece_buf, data_len)) {
        INFO("method GET\n");
        parse_buf->method_bit_map |= B_GET;
        rece_buf += (GET_STR_LEN+1);
        data_len -= (GET_STR_LEN+1);

        // parse file name
        int _file_name_len;
        _file_name_len = parse_file_name(rece_buf, data_len, parse_buf);
        rece_buf += (_file_name_len+1);
        data_len -= (_file_name_len+1);

        // parse version
        parse_http_version(rece_buf, data_len, parse_buf);
     
    } 
    /*
    else if (0 == strncmp(rece_buf, HEAD_STR, strlen(HEAD_STR))) {

        DEBUG("method HEAD\n");
        parse_buf->method_bit_map |= B_HEAD;
        
    } else if (0 == strncmp(rece_buf, POST_STR, strlen(POST_STR))) {

        DEBUG("method POST\n");
        parse_buf->method_bit_map |= B_POST;
    
    } else if (0 == strncmp(rece_buf, PUT_STR, strlen(PUT_STR))) {

        DEBUG("method PUT\n");
        parse_buf->method_bit_map |= B_PUT;
    
    } else if (0 == strncmp(rece_buf, DELETE_STR, strlen(DELETE_STR))) {

        DEBUG("method DELETE\n");
        parse_buf->method_bit_map |= B_DELETE;
    
    } else {

        DEBUG("parse method fail, unknown method\n");
        return FAIL;
    }
    */

    // after parsing, bit should be turned on
    assert( (parse_buf->parse_bit_map & B_METHOD) == 0);
    parse_buf->parse_bit_map |= B_METHOD;
    assert(parse_buf->method_bit_map != 0);
    return SUCC;
}


int parse_http_header (char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {
    
    INFO("in parse_http_header\n");


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


    // parse HOST, user-agent, accept, ...
    if (0 == strncmp(rece_buf, HOST_STR, strlen(HOST_STR))) {
        DEBUG("HOST get\n");
        parse_buf->parse_bit_map |= B_HOST;

        /*
        rece_buf += (strlen(HOST_STR)+1);
        if_fail = parse_host(rece_buf, data_len-strlen(HOST_STR)-1, parse_buf);
        */

    } else if (0 == strncmp(rece_buf, USER_AGENT_STR, strlen(USER_AGENT_STR))) {
        DEBUG("User-Agent get\n");
        parse_buf->parse_bit_map |= B_USER_AGENT;

        /*
        rece_buf += (strlen(USER_AGENT_STR)+1);
        */

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




int parse_file_name(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {


    // debug
    DEBUG("\t");
    for (int i=0; i<data_len; i++) {
        DEBUG("%c", rece_buf[i]);
    }
    DEBUG("\n");
    // end of debug


    
    // parse file name length
    int _len = 0;
    while (rece_buf[_len] != ' ') {
        _len ++;
    }
    DEBUG("file_name len = %d\n", _len);
  

    // file name
    parse_buf->file_name = (char*) malloc(sizeof(char)*(_len+1));
    strncpy(parse_buf->file_name, rece_buf, _len);
    DEBUG("file name = %s\n", parse_buf->file_name);

    return _len;
}


int parse_http_version(char* rece_buf, int data_len, struct parse_buf_t* parse_buf) {

    if (IF_MATCH_HTTP_10(rece_buf, data_len)) {
        DEBUG("http version 1.0\n");
        parse_buf->version = E_HTTP_10;

    } else if (IF_MATCH_HTTP_11(rece_buf, data_len)) {

        DEBUG("http version 1.1\n");
        parse_buf->version = E_HTTP_11;

    }

    return SUCC;
}

int parse_host(char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {

    // debug
    DEBUG("\t");
    for (int i=0; i<data_len; i++) {
        DEBUG("%c", rece_buf[i]);
    }
    DEBUG("\n");
    // end of debug

    return SUCC;

}


int reply_http(char* reply_buf, struct parse_buf_t* parse_buf) {
    
    INFO("in reply_http\n");

    char* start_reply_buf = reply_buf;
    int _offset = 0;

    _offset = add_http_startline(reply_buf, parse_buf);
    DEBUG("offset after add startline = %d\n", _offset);
    reply_buf += _offset;
    


    //add_http_date();
    
    //add_http_server();
    
    //add_http_last_modified();
    
    //add_http_etag();
    
    //add_http_accept_ranges();
    
    _offset = add_http_content_length(reply_buf, parse_buf);
    DEBUG("offset after add content_length = %d\n", _offset);
    reply_buf += _offset;

    //add_http_vary();
    
    _offset = add_http_content_type(reply_buf, parse_buf);
    DEBUG("offset after add add_http_content_type = %d\n", _offset);
    reply_buf += _offset;


    // add the last crlf
    memcpy(reply_buf, "\r\n", 2);
    DEBUG("offset after add the last crlf = %d\n", 2);
    reply_buf += 2;

    //add_http_file_data(reply_buf, parse_buf);
    

    // add file data
    FILE *fp;
    fp = fopen(parse_buf->file_name, "r");

    unsigned long remain_len = parse_buf->content_len;

    //char *_reply_buf = reply_buf + strlen(reply_buf);

    while (remain_len) {
        
        fread(reply_buf, REPLY_BUF_SIZE-_offset-1, 1, fp);
        
        write(parse_buf->fd, start_reply_buf, strlen(start_reply_buf));
        
        remain_len = (REPLY_BUF_SIZE-strlen(reply_buf)-1 > remain_len) ? 0 : remain_len - (REPLY_BUF_SIZE-strlen(reply_buf)-1) ; 

        if (remain_len) {
            reply_buf = start_reply_buf;
            _offset = 0;
            bzero(reply_buf, REPLY_BUF_SIZE);
        }
    }



    DEBUG("reply_buf =====\n%s\n", start_reply_buf);
    DEBUG("len = %d\n", (int)strlen(start_reply_buf));

    return SUCC;
}


int add_http_startline(char *reply_buf, struct parse_buf_t* parse_buf) {

    // "HTTP/1.1 200 OK\r\n"
    

    char* _reply_buf = reply_buf;


    // add http version
    switch (parse_buf->version) {
        case E_HTTP_10:
            memcpy(reply_buf, VERSION_10_STR, HTTP_VERSION_LEN);
            break;

        case E_HTTP_11:
            memcpy(reply_buf, VERSION_11_STR, HTTP_VERSION_LEN);
            break;

        case E_HTTP_12:
            memcpy(reply_buf, VERSION_12_STR, HTTP_VERSION_LEN);
            break;
    
    }
    reply_buf += HTTP_VERSION_LEN;
    memcpy(reply_buf, " ", 1);     // need a space
    reply_buf += 1;


    if ( parse_buf->method_bit_map & B_GET ) {
       
        if ( if_file_exist(parse_buf->file_name) ) {

            // paste status code
            parse_buf->reply_status = CODE_200;
            memcpy(reply_buf, CODE_200_STR, CODE_200_LEN);
            reply_buf += CODE_200_LEN;
            
        } else {

            // change return page to NOT_FOUND_PAGE
            parse_buf->file_name = (char*) realloc(parse_buf->file_name, strlen(NOT_FOUND_PAGE)+1);
            strcpy(parse_buf->file_name, NOT_FOUND_PAGE);


            // paste status code
            parse_buf->reply_status = CODE_404;
            memcpy(reply_buf, CODE_404_STR, CODE_404_LEN);
            reply_buf += CODE_404_LEN;
        }
    }
    
    memcpy(reply_buf, "\r\n", 2);
    reply_buf += 2;

    return (reply_buf-_reply_buf);
}


int add_http_content_length(char* reply_buf, struct parse_buf_t* parse_buf) {


    assert(NULL != parse_buf->file_name);

    char *_reply_buf = reply_buf;
    parse_buf->content_len = 0;
    FILE *fp;

    fp = fopen(parse_buf->file_name, "r");
    if ( NULL == fp ) {
        ERROR("Can not open file\n");
        return FAIL;
    }


    // count length
    while (EOF != (fgetc(fp)) ) {
        parse_buf->content_len ++;
    }


    // make sure it is end of file
    if ( ! feof(fp) ) {
        // get EOF but not reach end of file
        ERROR("Read file encounter error\n");
        return FAIL;
    }
    

    // convert long to string
    const int _len1 = snprintf(NULL, 0, "%lu", parse_buf->content_len);
    assert(_len1 > 0);
    char counter_str[_len1+1];
    int _len2 = snprintf(counter_str, _len1+1, "%lu", parse_buf->content_len);
    assert(counter_str[_len1] == '\0');
    assert(_len1 == _len2);


    // paste content length
    memcpy(reply_buf, CONTENT_LENGTH_STR, CONTENT_LENGTH_LEN);
    reply_buf += CONTENT_LENGTH_LEN;

    memcpy(reply_buf, counter_str, _len1);
    reply_buf += _len1;

    memcpy(reply_buf, "\r\n", 2);
    reply_buf += 2;
    

    fclose(fp);
    return (reply_buf - _reply_buf);
}


int add_http_content_type(char* reply_buf, struct parse_buf_t* parse_buf) {

    char* _reply_buf = reply_buf;

    memcpy(reply_buf, CONTENT_TYPE_STR, CONTENT_TYPE_LEN);
    reply_buf += CONTENT_TYPE_LEN;

    memcpy(reply_buf, TEXT_HTML, TEXT_HTML_LEN);
    reply_buf += TEXT_HTML_LEN;

    memcpy(reply_buf, "\r\n", 2);
    reply_buf += 2;

    return (reply_buf-_reply_buf);
}


int add_http_file_data(char* reply_buf, struct parse_buf_t* parse_buf) {
    return SUCC;    
}


bool if_file_exist(char *file_name) {

    // handle file name = /
    if (file_name[0] == '/' && file_name[1] == '\0') {
        
        file_name = (char*) realloc(file_name, strlen(INDEX_PAGE)+1);
        if (NULL == file_name) {
            ERROR("Can't realloc for file name\n");
            return FAIL;
        }
        strcpy(file_name, INDEX_PAGE);
        DEBUG("after realloc, file name = %s\n", file_name);
    } 

   
    // add a dot before /file_name
    if (file_name[0] == '/') {
        file_name = (char*) realloc(file_name, strlen(file_name)+1);
        if (NULL == file_name) {
            ERROR("Can't realloc for file name\n");
            return FAIL;
        }
        memmove(file_name+1, file_name, strlen(file_name));
        file_name[0] = '.';
    }


    // check if file accessable
    if ( -1 != access(file_name, F_OK) ) {
        // find file
        DEBUG("find file %s\n", file_name);
        return true;
        
    } else {
        // Can't find the file
        ERROR("Access file fail\n");
        return false;
    }
}



int clea_buf(struct parse_buf_t* parse_buf) {
    
    if (parse_buf->file_name) {
        free(parse_buf->file_name);
    }

    return SUCC;
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
