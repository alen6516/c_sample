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
    


int parse_header (char *rece_buf, int data_len) {

    if (MATCH_HOST(rece_buf, data_len)) {
        // parse_host()
    }
    return 0;
}



int parse (char *rece_buf, int data_len) {

    static char *start;
    start = rece_buf;
    static char *curr;
    curr = rece_buf;

    static bool is_header_end = false;
    static bool is_msg_end = false;
    static bool is_res = false;


    static char res_buf[100];
    static int res_len;


    while (curr-rece_buf <= data_len) {

        /* check if header end */
        if (*curr == CR && *(curr+1) == LF) {
            is_header_end = true;
           
            if (!is_res) {
                parse_header(rece_buf, curr-start);

            } else {
                /* if data reserved in res_buf */
                if (res_len + (curr-start) >= 100) {
                    // header is too long
                }
                strncat(res_buf, start, curr-start);
                parse_header(res_buf, res_len+(curr-start));
            }
            curr += 2;


            /* check if msg end */
            if (*(curr+2) == CR && *(curr+3) == LF) {
                is_msg_end = true; 
            }
        }
    }



    return 0;
}


int main () {
    
    char buf[] = "Host: this is  Host\r\n";
    int len = strlen(buf);
    parse(buf, len);

}
