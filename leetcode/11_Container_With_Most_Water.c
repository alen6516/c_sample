/*
Runtime: 12 ms, faster than 95.64% of C online submissions for Container With Most Water.
Memory Usage: 7.9 MB, less than 14.29% of C online submissions for Container With Most Water.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)  ((a)<(b) ? (a) : (b))

int maxArea(int* height, int heightSize) {

	if (heightSize == 2) return MIN(height[0], height[1]);
    
    unsigned short left_side = 0;
    unsigned short right_side = (unsigned short) (heightSize-1);
    int ret = (heightSize-1) * MIN(height[left_side], height[right_side]);

    int curr_area;
    for (int i=2; i<heightSize; i++) {

        if (height[left_side] > height[right_side]) {
            right_side --;

        } else {
            left_side ++;

        }

        if (right_side == left_side)
            break;

        curr_area = (heightSize-i) * MIN(height[left_side], height[right_side]);

        if (curr_area > ret) {
            ret = curr_area;
        }
    }
    return ret;
}

int main () {

    int arr[] = {1, 5, 6, 2, 5, 4, 8, 3, 7};
    printf("arr[] = [1, 5, 6, 2, 5, 4, 8, 3, 7]\n");
    printf("%d\n", maxArea(arr, 9));

}
