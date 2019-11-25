#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOT !

#define CR '\r'
#define LF '\n'


// Host: www.msn.com
#define MATCH_HOST(buf, len)        \
    (len >= 6       &&              \
     buf[0] == 'H'  &&              \
     buf[1] == 'o'  &&              \
     buf[2] == 's'  &&              \
     buf[3] == 't'  &&              \
     buf[4] == ':'  &&              \
     buf[5] == ' ')
    

struct parse_buf_t {
    unsigned char   is_header_end: 1,
                    is_msg_end :1;


    unsigned char   method_get: 1,
                    method_post: 1,
                    method_delete: 1;
    int content_len;
    int handled_len;
};


int parse_header (char *rece_buf, int data_len) {
    /*
    if (MATCH_HOST(rece_buf, data_len)) {
        // parse_host()
    }
    */
    printf("%s\n", rece_buf);

    return 0;
}


int parse_content (char *rece_buf, int data_len) {
    printf("%s\n", rece_buf);
    return 0;
}


int parse (char *rece_buf, int data_len) {

    static char *start;     /* start of a header */
    static char *curr;      /* moving pointer */

    static struct parse_buf_t parse_buf = {0};

    static char pres_buf[100];
    static int pres_len = 0;
    static int this_len;
   

    for (start=rece_buf, curr=rece_buf, this_len = 1;
         this_len < data_len && !parse_buf.is_msg_end;
         curr ++) {

        if (*curr == LF && *(curr-1) == CR) {
            // detect a header or msg ends

            if (parse_buf.is_header_end) {
                // end of msg
                parse_buf.is_msg_end = true;
                if (parse_buf.content_len) {
                    curr ++;
                    break;
                }

            } else {
                // end of header
                
                this_len = curr-start-1;

                parse_buf.is_header_end = true;
                if (pres_len) {
                    // if have preserve msg

                    if (this_len > 100-pres_len-1) {
                        // this header is too long
                    } else {
                        strncat(pres_buf, start, this_len);
                    }
                    parse_header(pres_buf, pres_len+this_len);
                    bzero(pres_buf, 100);
                    pres_len = 0;

                } else {
                    parse_header(start, this_len);
                }
            }
        } else {
            if (parse_buf.is_header_end) {
                // detect a new header starts
                parse_buf.is_header_end = false;
                start = curr;
            }

            if (curr-rece_buf == data_len-1) {
                // detect this rece_buf is over
                this_len = curr-start+1;

                pres_len += this_len;
                strncpy(pres_buf, start, this_len);
                return 0;
            }
        }
    }   /* end of for loop */


    // after the end of msg
    if (parse_buf.is_msg_end && parse_buf.content_len) {
        // pass content to parse_content
        
        parse_content(curr, data_len-(curr-start));
        parse_buf.handled_len += data_len-(curr-start);
        if (parse_buf.content_len == parse_buf.handled_len) {
            bzero((void*)&parse_buf, sizeof(struct parse_buf_t));
        }
    }

    return 0;
}        
    


int main () {
    
    char buf[] = "Host: this is  Host\r\nServer: my_server\r\n\r\n";
    int len = strlen(buf);
    parse(buf, len);

}
