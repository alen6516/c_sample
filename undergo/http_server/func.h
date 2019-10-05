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
    E_METHOD = 0,
    E_HOST,
    E_USER_AGENT,
    E_ACCEPT
    /* if more then 8 bits, modify struct parse_buf->parse_bit_map */
};

#define B_METHOD        (0x1 << E_METHOD)
#define B_HOST          (0x1 << E_HOST)
#define B_USER_AGENT    (0x1 << E_USER_AGENT)
#define B_ACCEPT        (0x1 << E_ACCEPT)



enum method_bit_enum {
    E_GET = 0,
    E_POST,
    E_HEAD,
    E_PUT,
    E_DELETE,
    E_TRACE,
    E_CONNECT,
    E_OPTIONS
    /* if more then 8 bits, modify struct parse_buf->method_bit_map */
};

#define B_GET       (0x1 << E_GET)
#define B_POST      (0x1 << E_POST)
#define B_HEAD      (0x1 << E_HEAD)
#define B_PUT       (0x1 << E_PUT)
#define B_DELETE    (0x1 << E_DELETE)
#define B_TRACE     (0x1 << E_TRACE)
#define B_CONNECT   (0x1 << E_CONNECT)
#define B_OPTIONS   (0x1 << E_OPTIONS)


enum http_version {
   E_HTTP_10 = 0,
   E_HTTP_11,
   E_HTTP_12
};


void *rece_http(void*);
int parse_http(char*, char*, struct parse_buf_t*);
    int parse_http_startline(char*, int, struct parse_buf_t*);
        int parse_file_name(char *, int, struct parse_buf_t*);
        int parse_http_version(char *, int, struct parse_buf_t*);

    int parse_http_header(char*, int, struct parse_buf_t*);
        int parse_host(char*, int, struct parse_buf_t*);

int reply_http(char*, struct parse_buf_t*);
    int add_http_startline(char*, struct parse_buf_t*);
    int add_http_content_length(char*, struct parse_buf_t*);
    int add_http_content_type(char*, struct parse_buf_t*);
    int add_http_file_data(char*, struct parse_buf_t*);

int clear_buf(struct parse_buf_t*);


bool if_file_exist(char*);
#endif
