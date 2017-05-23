#include <stdio.h>
#include "matrixchain.h"

int main(int argc, char *argv[]) {
    // 행렬이 모두 4개인 경우.
    // (100 x 1), (1 x 100), (100 x 1), (1 x 100)
    int p_of_A[] = {100, 1, 100, 1, 100};
    int count_of_p = sizeof(p_of_A)/sizeof(p_of_A[0]);
    int start_matrix_index = 1;
    int end_matrix_index = count_of_p - 1;
    int result = 0;
    
    result = minimumMatrixChainRecursive(p_of_A, start_matrix_index, end_matrix_index);
    printf("최소 곱셈 횟수: %d \n", result);
    
    return 0;
}
