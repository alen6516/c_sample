#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "define_http.h"

#define CR '\r'
#define LF '\n'

struct parse_buf_t {
    unsigned char is_msg_end :1,
                  is_prev_cr :1;

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
        printf("len = %d\n", parse_buf->remain_content_len);
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

    static char pres_buf[100];
    static int pres_len = 0;
   
    for (start=rece_buf, curr=rece_buf;
        curr-rece_buf < data_len;
        curr ++) {

        if (*curr == LF) {
            // detect a header or msg ends
            
            if (pres_len) {
                if (this_len > 100-pres_len-1) {
                    // this header is too long
                } else {
                    strncat(pres_buf, start, this_len);
                }
                
            }
            
            

            if (curr-start == 1) {
                // end of msg
                parse_buf.is_msg_end = true;
                
                if (parse_buf.remain_content_len == 0) {
                    reply_http(&parse_buf);
                    bzero((void*)&parse_buf, sizeof(struct parse_buf_t));
                }
            } else {
                // end of header
                
                this_len = curr-start+1-2;

                if (pres_len) {
                    // if have preserve msg

                    if (this_len > 100-pres_len-1) {
                        // this header is too long
                    } else {
                        strncat(pres_buf, start, this_len);
                    }
                    parse_header(pres_buf, pres_len+this_len, &parse_buf);
                    bzero(pres_buf, 100);
                    pres_len = 0;

                } else {
                    parse_header(start, this_len, &parse_buf);
                }
            }
        } else {
            if (parse_buf.is_msg_end && parse_buf.remain_content_len != 0) {
                // it is body
                
                this_len = (parse_buf.remain_content_len) > data_len-(curr-start) \
                            ? data_len-(curr-start): (parse_buf.remain_content_len);
                
                
                parse_body(curr, this_len, &parse_buf);
                parse_buf.remain_content_len -= this_len;
                curr += (this_len-1);
                if (parse_buf.remain_content_len == 0) {
                    bzero((void*)&parse_buf, sizeof(struct parse_buf_t));
                }
                
            } else {
                // it is next header
                start = curr;
                if (*curr == CR) {
                    parse_buf.is_prev_cr = true;
                } else {
                    parse_buf.is_prev_cr = false;
                }
            }

            if (curr-rece_buf == data_len-1 && !parse_buf.is_msg_end) {
                // detect this rece_buf is over but still headers
                this_len = curr-start+1;

                strncpy(pres_buf+pres_len, start, this_len);
                pres_len += this_len;
                return 0;
            }
        }
    }   /* end of for loop */


    return 0;
}        
    


int main () {
    
    char buf1[] = "Host: this is Host\r\nServer: my_server\r\n";
    int len = strlen(buf1);
    parse(buf1, len);
    char buf2[] = "Content-Length: 14\r\n\r\nthis is body.\n";
    len = strlen(buf2);
    parse(buf2, len);

}
