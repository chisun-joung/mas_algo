#include <stdio.h>
#include <stdlib.h>

int NQueen_Promising(int pPath[], int row)
{
    for (int i = 0; i < row; i++) {
        if (pPath[row] == pPath[i] || row - i == abs(pPath[row] - pPath[i]))
            return 1;
    }
    return 0;
}

void PrintQueens(int q[], int queenNum)
{
    int row = 0, col;
    for (row = 0; row < queenNum; row++) {
        for (col = 0; col < queenNum; col++) {
            if (q[row] == col) printf("Q");
            else printf("X");
        }
        printf("\n");
    }
    printf("\n");
}

void NQueen_BackTracking(int queenNum, int row, int pPath[])
{
    for (int i = 0; i < queenNum; i++) {
        pPath[row] = i;
        if (!NQueen_Promising(pPath, row)) {
            if (row == queenNum - 1) {
                PrintQueens(pPath, queenNum);
            } else {
                NQueen_BackTracking(queenNum, row + 1, pPath);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int queenNum = 8;
    int *pPath = malloc( sizeof(int) * queenNum );
    if (pPath != NULL) {
        NQueen_BackTracking(queenNum, 0, pPath);
        free(pPath);
    }
    
    return 0;
}