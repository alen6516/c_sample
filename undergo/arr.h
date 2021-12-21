#ifndef ARR_H
#define ARR_H

void arr_show(int *arr, int len)
{
    if (!len) {
        printf("arr = []");
    }
    printf("arr = [ %d, ", arr[0]);
    for (int i=1; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

#endif
