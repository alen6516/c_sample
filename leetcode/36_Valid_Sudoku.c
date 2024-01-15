#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "utils/arr.h"
#include "utils/utils.h"


bool check_same_row(char **input, int raw, int col)
{
    int val = input[raw][col];

    for (int j=0; j<9; j++) {
        if (j > col && val == input[raw][j]) {
            printf(" (%d, %d), is conflict with (%d, %d)\n", raw, col, raw, j);
            return false;
        }
    }

    return true;
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    
    // every number needs to check with 3 array:
    // 1. arr of its column
    // 2. arr of its row
    // 3. arr of its 3x3 block
    // if no such number in that array, fit in this number
    // else return false
    

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            check_same_row(board, i, j);
        }
    }
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
        ,{'6',' ',' ','1','9','5',' ',' ',' '}
        ,{' ','9','8',' ',' ',' ',' ','6',' '}
        ,{'8',' ',' ',' ','6',' ',' ',' ','3'}
        ,{'4',' ',' ','8',' ','3',' ',' ','1'}
        ,{'7',' ',' ',' ','2',' ',' ',' ','6'}
        ,{' ','6',' ',' ',' ',' ','2','8',' '}
        ,{' ',' ',' ','4','1','9',' ',' ','5'}
        ,{' ',' ',' ',' ','8',' ',' ','7','9'}};

#endif

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (j % 3 == 2)
                printf(" %c |", input[i][j]);
            else
                printf(" %c :", input[i][j]);
        }
        if ( i % 3 == 2)
            printf("\n===+===+===+===+===+===+===+===+===+\n");
        else
            printf("\n---+---+---+---+---+---+---+---+---+\n");
    }

    char **_input = &input[0];

    //isValidSudoku(_input, 9, NULL);
}
