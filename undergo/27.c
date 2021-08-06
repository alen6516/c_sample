#include <stdio.h>

int foo(int* arr, int len, int val)
{
    int head, tail;
    head = 0, tail = len-1;
    while(head < tail) {
        if (arr[head] == val) {
            while(head < tail) {
                if (arr[tail] == val) {
                    tail--;
                } else {
                    arr[head] = arr[tail];
                    arr[tail] = -1;
                    tail--;
                    break;
                }
            }
        }
        head++;
    }

    return (arr[head == val]) ?head : (head-1);
}

int main ()
{
    int arr[] = {1, 2, 5, 2, 4, 6, 1, 3, 3, 4};
    int len = sizeof(arr)/sizeof(arr[0]);
    int target = 2;

    printf("len = %d\n", len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
    printf("target = %d\n", target);

    int ret_len = foo(arr, len, target);

    printf("len = %d\n", ret_len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}
