

int parser(char *rece_buf, int data_len) {



    for () {
    
        if (!is_msg_end) {
            // header
            if (*curr == LF) {
                if (pres_len) {
                    strcpy()
                    pres_len += curr-start+1
                    start = pres_start;
                }

                if (it_is_\r\n) {
                    is_msg_end = true;
                    if (! content_len) {
                        zero(parse_buf)
                    }
                } else {
                    parse_header(start, (pres_len)? pres_len: curr-start+1)
                }

                if (pres_len) {
                    zero(pres_len);
                }
            }
        
        } else {
            // body
            copy_to_the_end_of_body_or_end_of_this_rece_buf
        
        }
    }
}
