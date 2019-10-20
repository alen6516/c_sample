#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct thr_list_t* thr_list;






int main () {
    thr_list = (struct thr_list_t*) malloc(sizeof(struct thr_list_t));
    bzero(thr_list, sizeof(struct thr_list_t));

    

}
