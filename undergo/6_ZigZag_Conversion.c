#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Runtime: 0 ms, faster than 100.00% of C online submissions for ZigZag Conversion.
 * Memory Usage: 7.7 MB, less than 100.00% of C online submissions for ZigZag Conversion.
 */


char * convert(char * s, int numRows) {

    if (numRows == 1 || strlen(s) == 1 || strlen(s) == 2 || strlen(s) <= numRows)
        return s;


    int len = strlen(s);

    char* ret = (char*) malloc(sizeof(char)*len+1);

    
    int start_off;          // offset of the first alphabat of this layer
    int step1, step2;       // 2 kinds of offset

    int tmp_offset;         // count total offset of the following alphabat
    int i=0;
    for (int lay=0; lay < numRows; lay++) {
        
        start_off = lay;
        step1 = (numRows - lay - 1) * 2;
        step2 = lay*2;

        
        ret[i++] = *(s+start_off);
        tmp_offset = start_off;

        while (1) {

            if (step1) {
                tmp_offset += step1;
                if (tmp_offset >= len)
                    break;
                
                ret[i++] = *(s+tmp_offset);
            }

            if (step2) {
                tmp_offset += step2;
                if (tmp_offset >= len)
                    break;

                ret[i++] = *(s+tmp_offset);
            }
        }
    }
    ret[i] = '\0';
    return ret;
}



int main() {



    char s1[] = "ABC";
    printf("before: %s\n", s1);
    printf("after : %s\n", convert(s1, 4));
    printf("expect: %s\n\n", "PINALSIGYAHRPI");

}
