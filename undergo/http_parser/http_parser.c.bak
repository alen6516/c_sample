#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "define_http.h"

#define CR '\r'
#define LF '\n'

struct parse_buf_t {
    unsigned char is_msg_end :1,
                  is_header_start : 1,
                  is_header_end :1;

    unsigned char method;
    int remain_content_len;
};


int parse_header (char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {
    /*
    if (MATCH_HOST(rece_buf, data_len)) {
        // parse_host()
    }
    */

    static char buf[100];
    strncpy(buf, rece_buf, data_len);
    buf[data_len] = 0;
    printf("%s\n", buf);


    if (0 == strncmp(CONTENT_LENGTH_STR, rece_buf, CONTENT_LENGTH_LEN)) {
        for (int i=CONTENT_LENGTH_LEN; i<data_len; i++) {
            parse_buf->remain_content_len *= 10;
            parse_buf->remain_content_len += (rece_buf[i]-'0');
        }
    }

    return 0;
}


int parse_body (char *rece_buf, int data_len, struct parse_buf_t* parse_buf) {
    static char buf[100];
    strncpy(buf, rece_buf, data_len);
    buf[data_len] = 0;
    printf("body: %s\n", buf);

    return 0;
}


int reply_http (struct parse_buf_t* parse_buf) {
    printf("in reply http\n");
    return 0;
}


int parse (char *rece_buf, int data_len) {

    static char *start;     /* start of a header */
    static char *curr;      /* moving pointer */
    static int this_len;

    static struct parse_buf_t parse_buf = {0};

    static char resrv_buf[100];
    static int resrv_len = 0;
   
    for (start=rece_buf, curr=rece_buf;
        curr-rece_buf < data_len;
        curr ++) {

        if (! parse_buf.is_header_start) {
            start = curr;
            parse_buf.is_header_start = true;
        }

            
        if (*curr == LF) {
            // header or msg end
            this_len = curr-start+1;

            if (resrv_len) {
                if (100-resrv_len <= this_len) {
                    // this header is too long
                
                } else {
                    strncpy(resrv_buf+resrv_len, start, this_len);
                    resrv_len += this_len;
                    this_len= resrv_len;
                    resrv_buf[this_len] = 0;
                    start = resrv_buf;
                }
            }

            if (*start == CR && *(start+1) == LF) {
                // detect msg end
                parse_buf.is_msg_end = true;
                this_len = data_len-(curr-start+1);
                if (parse_buf.remain_content_len && this_len) {
                    this_len = (this_len > parse_buf.remain_content_len) ? parse_buf.remain_content_len : this_len;
                    parse_body(curr+1, this_len, &parse_buf);
                    parse_buf.remain_content_len -= this_len;
                    curr += this_len;
                }
            } else {
                // detect header end
                parse_buf.is_header_end = true;
                parse_header(start, this_len-2, &parse_buf);
                parse_buf.is_header_start = false;
            }

            resrv_len = 0;

            if (parse_buf.is_msg_end && !parse_buf.remain_content_len) {
                bzero(&parse_buf, sizeof(struct parse_buf_t));
            }
        } else {
            if (data_len == curr-rece_buf+1) {
                // reach the end of rece_buf
                
                this_len = curr-start+1;
                
                if (100-resrv_len <= this_len) {
                    // this header is too long
                
                } else {
                    strncpy(resrv_buf+resrv_len, start, this_len);
                    resrv_len += this_len;
                    this_len= resrv_len;
                    resrv_buf[this_len] = 0;
                }
            }
        }
    }
    return 0;
}        
    


int main () {
    
    char buf1[] = "Host: this is Host\r\nServer: my_server\r";
    int len = strlen(buf1);
    parse(buf1, len);
    char buf2[] = "\rContent-Length: 14\r\n";
    len = strlen(buf2);
    parse(buf2, len);
    char buf3[] = "\r\nthis is body.\n";
    len = strlen(buf3);
    parse(buf3, len);
}
