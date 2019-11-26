#ifndef DEFINE_HTTP_H
#define DEFINE_HTTP_H


/* both request and rely */
#define HTTP_VERSION_LEN 8

#define VERSION_10_STR "HTTP/1.0"
#define IF_MATCH_HTTP_10(s, len)   \
    (len >= HTTP_VERSION_LEN    && \
     s[0]=='H'                  && \
     s[1]=='T'                  && \
     s[2]=='T'                  && \
     s[3]=='P'                  && \
     s[4]=='/'                  && \
     s[5]=='1'                  && \
     s[6]=='.'                  && \
     s[7]=='0')


#define VERSION_11_STR "HTTP/1.1"
#define IF_MATCH_HTTP_11(s, len)   \
    (len >= HTTP_VERSION_LEN    && \
     s[0]=='H'                  && \
     s[1]=='T'                  && \
     s[2]=='T'                  && \
     s[3]=='P'                  && \
     s[4]=='/'                  && \
     s[5]=='1'                  && \
     s[6]=='.'                  && \
     s[7]=='1')


#define VERSION_12_STR "HTTP/1.2"
#define IF_MATCH_HTTP_12(s, len)   \
    (len >= HTTP_VERSION_LEN    && \
     s[0]=='H'                  && \
     s[1]=='T'                  && \
     s[2]=='T'                  && \
     s[3]=='P'                  && \
     s[4]=='/'                  && \
     s[5]=='1'                  && \
     s[6]=='.'                  && \
     s[7]=='2')
/* end of both */


/* request */
#define METHOD_GET_LEN 4
#define IF_MATCH_METHOD_GET(s, len)    \
    (len >= METHOD_GET_LEN          && \
     s[0]=='G'                      && \
     s[1]=='E'                      && \
     s[2]=='T'                      && \
     s[3]==' ')

#define METHOD_HEAD_LEN 5
#define IF_MATCH_METHOD_HEAD(s, len)   \
    (len >= METHOD_HEAD_LEN         && \
     s[0]=='H'                      && \
     s[1]=='E'                      && \
     s[2]=='A'                      && \
     s[3]=='D'                      && \
     s[4]==' ')


#define METHOD_POST_LEN 5
#define IF_MATCH_METHOD_POST(s, len)   \
    (len >= METHOD_POST_LEN         && \
     s[0]=='P'                      && \
     s[1]=='O'                      && \
     s[2]=='S'                      && \
     s[3]=='T'                      && \
     s[4]==' ')


#define METHOD_PUT_LEN 4
#define IF_MATCH_METHOD_PUT(s, len)    \
    (len >= METHOD_PUT_LEN          && \
     s[0]=='P'                      && \
     s[1]=='U'                      && \
     s[2]=='T'                      && \
     s[3]==' ')


#define METHOD_DELETE_LEN 7
#define IF_MATCH_METHOD_DELETE(s, len) \
    (len >= METHOD_DELETE_LEN       && \
     s[0]=='D'                      && \
     s[1]=='E'                      && \
     s[2]=='L'                      && \
     s[3]=='E'                      && \
     s[4]=='T'                      && \
     s[5]=='E'                      && \
     s[6]==' ')


#define HOST_STR_LEN 6
#define IF_MATCH_HOST(s, len)  \
    (len >= HOST_STR_LEN    && \
     s[0]=='H'              && \
     s[1]=='o'              && \
     s[2]=='s'              && \
     s[3]=='t'              && \
     s[4]==':'              && \
     s[5]==' ')


#define USER_AGENT_STR_LEN 12
#define IF_MATCH_USER_AGENT(s, len)         \
    (len >= USER_AGENT_STR_LEN           && \
     s[0]=='U' && s[1]=='s' && s[2]=='e' && \
     s[3]=='r' && s[4]=='-' && s[5]=='A' && \
     s[6]=='g' && s[7]=='e' && s[8]=='n' && \
     s[9]=='t' && s[10]==':' && s[11]==' ')



#define CONNECTION_STR_LEN 12
#define IF_MATCH_CONNECTION(s, len)         \
    (len >= CONNECTION_STR_LEN           && \
     s[0]=='C' && s[1]=='o' && s[2]=='n' && \
     s[3]=='n' && s[4]=='e' && s[5]=='c' && \
     s[6]=='t' && s[7]=='i' && s[8]=='o' && \
     s[9]=='n' && s[10]== ':' && s[11]==' ')


#define KEEPALIVE_STR_LEN 10
#define IF_MATCH_KEEPALIVE(s, len)         \
    (len >= KEEPALIVE_STR_LEN            && \
     s[0]=='k' && s[1]=='e' && s[2]=='e' && \
     s[3]=='p' && s[4]=='-' && s[5]=='a' && \
     s[6]=='l' && s[7]=='i' && s[8]=='v' && \
     s[9]=='e')


#define REQUEST_LINE_BUF_LEN 100
#define HOST_BUF_LEN 100
#define USER_AGENT_BUF_LEN 100


#define DATE_STR_LEN 6
#define DATE_STR "Date: "
#define DATE_FORMAT_LEN 30
#define DATE_FORMAT "%a, %d %b %Y %X GMT"

#define SERVER_STR_LEN 30
#define SERVER_STR "Server: MyServer/0.0.1 (Linux)"


#define LAST_MODIFIED_STR_LEN 15
#define LAST_MODIFIED_STR   "Last-Modified: "

#define ACCEPT_STR      "Accept:"
/* end of request */


/* reply */
#define CODE_200 200    // 200 ok
#define CODE_400 400    // 400 bad request
#define CODE_404 404    // 404 not found
#define CODE_405 405    // 405 Method Not Allowed
#define CODE_414 414    // 414 URI Too Long
#define CODE_500 500    // 500 Internal Server Error
#define CODE_505 505    // 505 HTTP Version Not Supported


#define CODE_200_STR "200 OK"
#define CODE_200_LEN 6

#define CODE_400_STR "400 Bad Request"
#define CODE_400_LEN 15

#define CODE_404_STR "404 Not Found"
#define CODE_404_LEN 13

#define CODE_405_STR "405 Method Not Allowed"
#define CODE_405_LEN 22

#define CODE_414_STR "414 URI Too Long"
#define CODE_414_LEN 16

#define CODE_500_STR "500 Internal Server Error"
#define CODE_500_LEN 25

#define CODE_505_STR "505 HTTP Version Not Supported"
#define CODE_505_LEN 30

#define CONTENT_TYPE_STR    "Content-Type: "
#define CONTENT_TYPE_LEN    14

    #define ETX_HTML        "html"
    #define TEXT_HTML       "text/html"
    #define TEXT_HTML_LEN   9

    #define EXT_PNG         "png"
    #define IMAGE_PNG       "image/png"
    #define IMAGE_PNG_LEN   9

    #define EXT_JPG         "jpg"
    #define IMAGE_JPG       "image/jpg"
    #define IMAGE_JPG_LEN   9

    #define EXT_JPEG        "jpeg"
    #define IMAGE_JPEG      "image/jpeg"
    #define IMAGE_JPEG_LEN  10


#define CONTENT_LENGTH_STR  "Content-Length: "
#define CONTENT_LENGTH_LEN  16
/* end of reply */


#define MAX_URI_LEN 30


enum method_type_enum {
    E_UNKNOEN = 0,
    E_GET,
    E_POST,
    E_HEAD,
    E_PUT,
    E_DELETE,
    E_TRACE,
    E_CONNECT,
    E_OPTIONS
    /* if more then 8 bits, modify struct parse_buf->method_bit_map */
};


enum http_version {
   E_HTTP_10 = 0,
   E_HTTP_11,
   E_HTTP_12
};

#endif
