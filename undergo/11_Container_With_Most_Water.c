#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)  ((a)<(b) ? (a) : (b))


int maxArea(int* height, int heightSize){

    int left_side = 0;
    int right_side = heightSize-1;
    int ret = (heightSize-1) * MIN(height[left_side], height[right_side]);


    for (int i=2; i<heightSize; i++) {
        
        if (height[left_side] > height[right_side]) {
            right_side --;
            //printf("now right_side is %d\n", height[right_side]);

        } else {
            left_side ++;
            //printf("now left_side is %d\n", height[left_side]);

        }

        if (right_side == left_side)
            break;

        //curr_area = (heightSize-i) * MIN(height[left_side], height[right_side]);
        //printf("this area is %d * %d = %d\n", heightSize-i, MIN(height[left_side], height[right_side]), curr_area);

        ret = ( (heightSize-i) * MIN(height[left_side], height[right_side]) > ret ) ? (heightSize-i) * MIN(height[left_side], height[right_side]) : ret;
    }

    return ret;
}

int main () {

    int arr[] = {1, 5, 6, 2, 5, 4, 8, 3, 7};
    printf("arr[] = [1, 5, 6, 2, 5, 4, 8, 3, 7]\n");
    printf("%d\n", maxArea(arr, 9));

}
