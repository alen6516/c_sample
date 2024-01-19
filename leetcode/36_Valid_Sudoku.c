#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "utils/arr.h"
#include "utils/utils.h"


// Todo: use a bool arr[9] to store the number that is appeared during check_raw/col/zone
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {

    // every number needs to check with 3 array:
    // 1. arr of its column
    // 2. arr of its row
    // 3. arr of its 3x3 block
    // if no such number in that array, fit in this number
    // else return false

    char val;

    for (int raw=0; raw<9; raw++) {
        for (int col=0; col<9; col++) {
            val = *(*(board+raw)+col);

            //printf("(%d, %d) = %c\n", raw, col, val);
            if (val == '.') continue;

            // check the same raw
            for (int j=0; j<9; j++) {
                if (j > col && val == *(*(board+raw)+j)) {
                    printf("    raw: (%d, %d), is conflict with (%d, %d)\n", raw, col, raw, j);
                    return false;
                }
            }

            // check the same col
            for (int i=0; i<9; i++) {
                if (i > raw && val == *(*(board+i)+col)) {
                    printf("    col: (%d, %d), is conflict with (%d, %d)\n", raw, col, i, col);
                    return false;
                }
            }

            // check the same zone
            for (int i=(raw/3)*3; i<(raw/3)*3+3; i++) {
                for (int j=(col/3)*3; j<(col/3)*3+3; j++) {
                    if ((9*raw+col) < (9*i+j) && val == *(*(board+i)+j)) {
                        printf("    zone: (%d, %d), is conflict with (%d, %d)\n", raw, col, i, j);
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
#if 0
    srand(time(NULL));
    int input[9][9];

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            input[i][j] = rand() % 10;
        }
    }

#else

    char input[9][9] = {
         {'5','3',' ',' ','7',' ',' ',' ',' '}
        ,{'5',' ',' ','1','9','5',' ',' ',' '}
        ,{' ','9','8',' ',' ',' ',' ','6',' '}
        ,{'8',' ',' ',' ','6',' ',' ',' ','3'}
        ,{'4',' ',' ','8',' ','3',' ',' ','1'}
        ,{'7',' ',' ',' ','2',' ',' ',' ','6'}
        ,{' ','6',' ',' ',' ',' ','2','8',' '}
        ,{' ',' ',' ','4','1','9',' ',' ','5'}
        ,{' ',' ',' ',' ','8',' ',' ','7','9'}};

    char *p[9];
    for (int i=0; i<9; i++)
        p[i] = input[i];

    char **pp = p;
#endif

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (j % 3 == 2)
                printf(" %c |", *(*(pp+i)+j));
            else
                printf(" %c :", *(*(pp+i)+j));
        }
        if ( i % 3 == 2)
            printf("\n===+===+===+===+===+===+===+===+===+\n");
        else
            printf("\n---+---+---+---+---+---+---+---+---+\n");
    }

    isValidSudoku(pp, 9, NULL);
}
