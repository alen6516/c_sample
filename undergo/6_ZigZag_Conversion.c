#include <stdio.h>

#include <string.h>


char * convert(char * s, int numRows) {

    int len = strlen(s);
    char ret[len];
    
    int start_off;
    int step1;
    int step2;

    int tmp_offset;
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
    printf("before: %s\nafter : %s\n", s, ret);
    return NULL;
}



int main() {

    char s[] = "PAYPALISHIRING";
    convert(s, 3);
    printf("expect: %s\n", "PAHNAPLSIIGYIR");


    char s1[] = "PAYPALISHIRING";
    convert(s1, 4);
    printf("expect: %s\n", "PINALSIGYAHRPI");

}
