#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[4];
} item_t;

item_t* init_item() {
    return (item_t*) malloc(sizeof(item_t));
}

int main () {
    item_t** ptr;
    item_t* arr[3];
    ptr = arr;

    arr[1] = init_item();

    arr[1]->name[0] = 'a';
    arr[1]->name[1] = 'b';
    arr[1]->name[2] = 'c';
    arr[1]->name[3] = '\0';

    printf("%s\n", (*(ptr+1))->name);

}
