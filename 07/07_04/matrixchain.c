#include "matrixchain.h"

int minimumMatrixChainRecursive(int p[], int i, int j) {
    int k = 0;
    int min = 9999999;
    int value = 0;

    if(i == j)
        return 0;
    
    for (k = i; k <j; k++) {
        value = minimumMatrixChainRecursive(p, i, k)
                    + minimumMatrixChainRecursive(p, k+1, j)
                    + p[i-1]*p[k]*p[j];
        
        if (value < min)
            min = value;
    }
    
    return min;
}
