#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "utils/arr.h"
#include "utils/utils.h"


bool check_same_row(char **p, int raw, int col)
{
    char *input = (char *)p;
    char val = *(input + 9*raw + col);
    //printf("(%d, %d) = %c\n", raw, col, val);

    for (int j=0; j<9; j++) {
        if (j > col && val != ' ' && val == *(input + 9*raw + j)) {
            printf(" (%d, %d), is conflict with (%d, %d)\n", raw, col, raw, j);
            return false;
        }
    }

    return true;
}

bool check_same_col(char **p, int raw, int col)
{
    char *input = (char *)p;
    char val = *(input + 9*raw + col);
    //printf("(%d, %d) = %c\n", raw, col, val);

    for (int i=0; i<9; i++) {
        if (i > raw && val != ' ' && val == *(input + 9*i + col)) {
            printf(" (%d, %d), is conflict with (%d, %d)\n", raw, col, i, col);
            return false;
        }
    }

    return true;
}

bool check_same_zone(char **p, int raw, int col)
{
    char val = *(*(p+raw)+col);
    printf("(%d, %d) = %c\n", raw, col, val);
    return true;

    for (int i=(raw/3)*3; i<(raw/3)*3+3; i++) {
        for (int j=(col/3)*3; j<(col/3)*3+3; j++) {
            if ((9*raw+col) < (9*i+j) &&
                val != ' ' && val == *(*(p+i)+j)) {
                printf(" (%d, %d), is conflict with (%d, %d)\n", raw, col, i, j);
                return false;
            }
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
    

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            //check_same_row(board, i, j);
            //check_same_col(board, i, j);
            check_same_zone(board, i, j);
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
        ,{' ',' ',' ','1','9','5',' ',' ',' '}
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
