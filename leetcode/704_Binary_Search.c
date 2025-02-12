

int search(int* nums, int numsSize, int target) {

    int start, mid, end;
    start = 0, end = numsSize-1;
    while (start != end) {
        mid = (start+end)/2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) {
            if (end-start == 1) {
                if (nums[end] == target) return end;
                else break;
            } else start=mid;
        }
        else end=mid;
    }
    return -1;
}

int main() {
    int nums[] = {-1, 0, 3, 5, 9, 12};  // Example array
    int target = 9;  // Target to search for
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = search(nums, numsSize, target);
    if (result != -1) {
        printf("Target found at index: %d\n", result);
    } else {
        printf("Target not found\n");
    }

    return 0;
}
