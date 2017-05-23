#include <stdio.h>
#include "ed.h"

int main(int argc, const char * argv[]) {
    char string1[] = "sunday";
    char string2[] = "saturday";
    
    int m = (int)strlen(string1);
    int n = (int)strlen(string2);
    int nED = ED_Recursive( string1, string2, m, n );
    printf("[%s]와 [%s]의 Edit Distance 길이(분할 정복): %d\n", string1, string2, nED);
    
    nED = ED_DP( string1, string2, m, n );
    printf("[%s]와 [%s]의 Edit Distance 길이(동적 계획법): %d\n", string1, string2, nED);
    
    nED = ED_DP( string2, string1, n, m );
    printf("[%s]와 [%s]의 Edit Distance 길이(동적 계획법): %d\n", string2, string1, nED);
    
    return 0;
}
