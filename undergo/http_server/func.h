#ifndef FUNC_H
#define FUNC_H

#include <stdint.h>
#include <stdbool.h>


/* both request and rely */
#define VERSION_10_STR "HTTP/1.0"
#define VERSION_11_STR "HTTP/1.1"
#define VERSION_12_STR "HTTP/1.2"
/* end of both */


/* request */
#define GET_STR     "GET"
#define HEAD_STR    "HEAD"
#define POST_STR    "POST"
#define PUT_STR     "PUT"
#define DELETE_STR  "DELETE"

#define HOST_STR        "Host:"
#define USER_AGENT_STR  "User-Agent:"
#define ACCEPT_STR      "Accept:"
/* end of request */


/* reply */
#define CODE_200 200    // 200 ok
#define CODE_400 400    // 400 bad request
#define CODE_403 403    // 403 forbidden
#define CODE_404 404    // 404 not found


#define CODE_200_STR    "200 OK"
//#define CODE_403_STR    ""
#define CODE_404_STR    "404 Not Found"


#define CONTENT_TYPE_STR    "Content-Type:"
    #define TEXT_HTML       "text/html"
#define CONTENT_LENGTH_STR  "Content-Length:"
/* end of reply */


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
    int parse_http_startline(char*, int, struct parse_buf_t*);
        int parse_file_name(char *, int, struct parse_buf_t*);
        int parse_http_version(char *, int, struct parse_buf_t*);

    int parse_http_header(char*, int, struct parse_buf_t*);
        int parse_host(char*, int, struct parse_buf_t*);

int reply_http(char*, struct parse_buf_t*);
    bool if_file_exist(char*);

    int add_content_length(char*, char*);

#endif
