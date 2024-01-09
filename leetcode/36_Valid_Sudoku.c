#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "utils/arr.h"
#include "utils/utils.h"


bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    
    // every number needs to check with 3 array:
    // 1. arr of its column
    // 2. arr of its row
    // 3. arr of its 3x3 block
    // if no such number in that array, fit in this number
    // else return false
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int input[9][9];

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            input[i][j] = rand() % 10;
        }
    }

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (input[i][j] == 0)
                printf("   |");
            else
                printf(" %d |", input[i][j]);
        }
        printf("\n---+---+---+---+---+---+---+---+---+\n");
    }
}
