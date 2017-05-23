#include <stdio.h>
#include "fibonacci.h"

int main()
{
    int result = 0;
    int n = 10;

    result = fibonacci_Recursive( n );
    printf("분할 정복법 fibonacci_Recursive(%d) = %d\n", n, result);

    result = fibonacci_DP( n );
    printf("동적 계획법 fibonacci_Recursive(%d) = %d\n", n, result);

    return 0;
}
