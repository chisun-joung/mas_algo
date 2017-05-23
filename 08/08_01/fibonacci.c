#include "fibonacci.h"

int fibonacci_Recursive(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci_Recursive(n-1) + fibonacci_Recursive(n-2);
}

int fibonacci_DP(int n) {
	int ret = 0;
	int *f_data = NULL;
    
    if (n == 0)
        return 0;
    else if (n <= 2)
        return 1;
    
    f_data = (int*)malloc(sizeof(int) * n);
    if (f_data != NULL) {
        f_data[0] = f_data[1] = 1;
        
        for(int i = 2; i < n; i++) {
            f_data[i] = f_data[i-1] + f_data[i-2];
        }
		ret = f_data[n - 1];
        free(f_data);
    }
    
    return ret;
}
