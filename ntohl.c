/***
 File Name: ntohl.c
 Author: alen6516
 Created Time: 2019-06-21
***/

#ifndef _STDINT_H
#include <stdint.h>
#endif

uint32_t ntohl(uint32_t netlong) {

    union {
        uint16_t num;
        uint8_t bytes[2];
    } endian_test = { .bytes ={ 0x01, 0x00 }};

    
    if (endian_test.num == 0x0001) {
        netlong = (netlong << 24) | \
                 ((netlong & 0xff00ul) << 8) | \
                 ((netlong & 0xff0000ul) >> 8) | \
                 (netlong >> 24);
    }

    return netlong;
}


/*

#include <stdio.h>
int main () {
   
    uint8_t pb[] = {0x11, 0x22, 0x33, 0x44};
    uint32_t *p, val;
    p = (uint32_t *) pb;
    val = *p;

    printf("%x\n", val);
    printf("%x\n", ntohl(val));

}

*/
