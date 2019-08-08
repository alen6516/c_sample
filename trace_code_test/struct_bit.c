#include <stdio.h>
#include <stdlib.h>

typedef struct {
    
    unsigned char   f0_t4:  5,
                    f5_t5:  1,
                    f6_t6:  1,
                    f7_t7:  1;
} item_t;




int main () {

    item_t* aaa;
    aaa = (item_t*) malloc(sizeof(item_t));

    aaa->f0_t4 = 0x0f;
    

}

