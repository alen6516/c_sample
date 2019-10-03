#ifndef FUNC_H
#define FUNC_H

#include <stdint.h>

#define GET_PRE_STR     "GET "
#define HEAD_PRE_STR    "HEAD "
#define POST_PRE_STR    "POST "
#define PUT_PRE_STR     "PUT "
#define DELETE_PRE_STR  "DELETE "

#define GET_PRE_LEN     4
#define POST_PRE_LEN    5
#define HEAD_PRE_LEN    5
#define PUT_PRE_LEN     4
#define DELETE_PRE_LEN  7
#define TRACE_PRE_LEN   6
#define CONNECT_PRE_LEN 8
#define OPTIONS_PRE_LEN 8


#define VERSION_10_STR "HTTP/1.0"
#define VERSION_11_STR "HTTP/1.1"
#define VERSION_12_STR "HTTP/1.2"

#define VERSION_10_len 8
#define VERSION_11_len 8
#define VERSION_12_len 8


#define CODE_200 200    // 200 ok
#define CODE_400 400    // 400 bad request
#define CODE_404 404    // 404 not found

#define CODE_200_STR    "200 OK"
#define CODE_200_len    6



struct parse_buf_t {
    uint8_t parse_bit_map;
    uint8_t method_bit_map;

    /* data parsed from received packet */
    char *method;
    char *host;
    char *user_agent;
    char *accept;


    unsigned short reply_status;
    char *file_name;
    unsigned char version;
};


enum parse_bit_enum {
    e_method = 0,
    e_host,
    e_user_agent,
    e_accept
    /* if more then 8 bits, modify struct parse_buf->parse_bit_map */
};

#define B_METHOD        (0x1 << e_method)
#define B_HOST          (0x1 << e_host)
#define B_USER_AGENT    (0x1 << e_user_agent)
#define B_ACCEPT        (0x1 << e_accept)



enum method_bit_enum {
    e_get = 0,
    e_post,
    e_head,
    e_put,
    e_delete,
    e_trace,
    e_connect,
    e_options
    /* if more then 8 bits, modify struct parse_buf->method_bit_map */
};

#define B_GET       (0x1 << e_get)
#define B_POST      (0x1 << e_post)
#define B_HEAD      (0x1 << e_head)
#define B_PUT       (0x1 << e_put)
#define B_DELETE    (0x1 << e_delete)
#define B_TRACE     (0x1 << e_trace)
#define B_CONNECT   (0x1 << e_connect)
#define B_OPTIONS   (0x1 << e_options)


enum http_version {
   e_http_10 = 0,
   e_http_11,
   e_http_12
};


void *rece_http(void*);

int parse_http(char*, char*, struct parse_buf_t*);
int _parse_http(char*, int, struct parse_buf_t*);
int parse_http_method(char*, int, struct parse_buf_t*);

int parse_file_name(char *, int, struct parse_buf_t*);
int parse_http_version(char *, int, struct parse_buf_t*);

int parse_host(char*, int, struct parse_buf_t*);

int reply_http(char*, struct parse_buf_t*);

#endif
