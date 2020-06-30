/***
 File Name: char_match.c
 Author: alen6516
 Created Time: 2019-06-24
***/

/*
 * give a byte array data[], and target
 * if data contain target, then find where it is
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

    unsigned char data[3] = {0b11100111, 0b00101100, 0b11110000};
    
    unsigned char target = 0b11001111;


    // show data
    for (int i=0; i<3; i++) {
        for (int j=7; j>=0; j--) {
            printf("%d", ( data[i] >> j ) & 0x1);
        }
        printf(", ");
    }
    printf("\n");

    
    // show target
    for (int j=7; j>=0; j--) {
        printf("%d", ( target >> j ) & 0x1);
    }
    printf("\n");


    int current_match = 0;

    int data_big = 0;
    int data_small = 7;

    int target_small = 7;

    int start_big = -1;
    int start_small = -1;

    int previus_match = 0;

    while ( data_big <= 2 ) {
    
        int current_data_bit = ( data[data_big] >> data_small ) & 0x1;
        int current_target_bit = ( target >> target_small ) & 0x1;

        printf("current_data_bit = %d, current_target_bit = %d, (target_small = %d)\n", current_data_bit, current_target_bit, target_small);

        if (current_data_bit == current_target_bit) {
            printf("bit match\n");

            if (!previus_match) {
            
                start_big = data_big;
                start_small = data_small;
                previus_match = 1;
            }

            target_small--;

            current_match++;
            if (current_match == 8) {
                break;
            }

        } else {
            previus_match = 0;
            current_match = 0;
            target_small = 7;
        }

        data_small--;
        if (data_small < 0) {
            printf("next byte\n");
            data_big++;
            data_small = 7;
        }
    }

    printf("big = %d, small = %d\n", start_big, start_small);
}
