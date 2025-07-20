#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/arr.h"


// Heapify function to maintain max-heap property
static void heapify(int *arr, int len, int i) {
    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child

    // If left child is larger than root
    if (left < len && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than current largest
    if (right < len && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        SWAP(arr[i], arr[largest]);

        // Recursively heapify the affected subtree
        heapify(arr, len, largest);
    }
}

// Main heap sort function
static void bheap_sort(int *arr, int len) {
    // Step 1: Build max heap (rearrange array)
    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(arr, len, i);

    // Step 2: Extract elements from heap one by one
    for (int i = len - 1; i > 0; i--) {
        // Move current root to end
        SWAP(arr[0], arr[i]);

        // Heapify reduced heap
        heapify(arr, i, 0);
    }
}

// Driver code
void show_bheap_sort(int *arr_in, int len) {
    int *arr_out = (int *)malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);
    printf("bheap_sort: =============================\n");

    CLOCK_START();
    bheap_sort(arr_out, len);
    CLOCK_END();

    arr_show(arr_out, len);
    printf("total: %f sec\n", CLOCK_DIFF_SEC());

    free(arr_out);
}
