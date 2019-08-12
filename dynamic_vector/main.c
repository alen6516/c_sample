#include <stdio.h>
#include <stdlib.h>

#include "vector.h"


int main () {


    int i;

    vector v;
    vector_init(&v);


    vector_add(&v, (void*) "Bonjour");
    vector_add(&v, (void*) "tout");
    vector_add(&v, (void*) "le");
    vector_add(&v, (void*) "monde");


    for (i=0; i < vector_total(&v); i++)
        printf("%s\n", (char*) vector_get(&v, i));
    printf("\n");


    vector_delete(&v, 3);
    vector_delete(&v, 2);
    vector_delete(&v, 1);


    vector_set(&v, 0, (void*) "Hello");
    vector_add(&v, (void*) "World");


    for (i=0; i<vector_total(&v); i++)
        printf("%s ", (char*) vector_get(&v, i));
    printf("\n");


    vector_free(&v);
}
