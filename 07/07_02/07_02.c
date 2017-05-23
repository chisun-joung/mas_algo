#include <stdio.h>

int factorial(int n) {
    int ret = 0;
    
    if (n <= 1) {
        ret = 1;
    }
    else {
        ret = n * factorial(n - 1);
    }
    
    return ret;
}

int main(int argc, char *argv[]) {
    int input_value = 4;
    int	result = 0;
    
    result = factorial(input_value);
    printf("%d! = %d\n", input_value, result);
    
    return 0;
}
