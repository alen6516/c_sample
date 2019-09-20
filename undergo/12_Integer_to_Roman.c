#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char * intToRoman(int num) {


    char ret[50];
    int curr_pos = 0;

    int remain = num;
    int curr = 0;



    // 1000
    if ( (curr = remain / 1000) ) {
    
        for (int i=0; i<curr; i++) {
            ret[curr_pos++] = 'M';
        }
        remain %= 1000;
    }
    

    // 100
    if ( (curr = remain / 100) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_pos++] = 'C';
            }

        } else if (curr == 4) {
            ret[curr_pos++] = 'C';
            ret[curr_pos++] = 'D';

        } else if (curr < 9) {
            ret[curr_pos++] = 'D';
            for (int i=5; i<curr; i++) {
                ret[curr_pos++] = 'C';
            }
        } else if (curr == 9) {
            ret[curr_pos++] = 'C';
            ret[curr_pos++] = 'M';
        }
        remain %= 100;
    }

    // 10
    if ( (curr = remain / 10) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_pos++] = 'X';
            }

        } else if (curr == 4) {
            ret[curr_pos++] = 'X';
            ret[curr_pos++] = 'L';

        } else if (curr < 9) {
            ret[curr_pos++] = 'L';
            for (int i=5; i<curr; i++) {
                ret[curr_pos++] = 'X';
            }
        } else if (curr == 9) {
            ret[curr_pos++] = 'X';
            ret[curr_pos++] = 'C';
        }
        remain %= 10;
    }


    // 1
    if ( (curr = remain) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_pos++] = 'I';
            }

        } else if (curr == 4) {
            ret[curr_pos++] = 'I';
            ret[curr_pos++] = 'V';

        } else if (curr < 9) {
            ret[curr_pos++] = 'V';
            for (int i=5; i<curr; i++) {
                ret[curr_pos++] = 'I';
            }
        } else if (curr == 9) {
            ret[curr_pos++] = 'I';
            ret[curr_pos++] = 'X';
        }
    }


    ret[curr_pos] = '\0';
    char *q = (char*) malloc(sizeof(char)*strlen(ret)+1);
    strcpy(q, ret);
    q[curr_pos] = '\0';
    return q;
}

int main () {


}
