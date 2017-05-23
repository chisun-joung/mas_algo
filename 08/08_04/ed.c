#include "ed.h"

int min3(int a, int b, int c) {
    if (a < b && a < c) {
        return a;
    } else if (b < c) {
        return b;
    }
    else {
        return c;
    }
}

int  ED_Recursive(char *string1, char *string2, int m, int n )
{
    if (m == 0)
        return n;

    if (n == 0)
        return m;
    
    if (string1[m - 1] == string2[n - 1])
        return ED_Recursive(string1, string2, m - 1, n - 1);
    else
        return 1 + min3(ED_Recursive(string1, string2, m, n-1),
                       ED_Recursive(string1, string2, m-1, n),
                       ED_Recursive(string1, string2, m-1, n-1));
}

int  ED_DP(char *string1, char *string2, int m, int n )
{
    int ret = 0;
    if (m == 0 || n == 0)
        return 0;
    
    int **ppValues = NULL;
    ppValues = (int**)malloc(sizeof(int*) * (m + 1));
    if (ppValues == NULL) {
        return ret;
    }
    for(int i = 0; i < m + 1; i++) {
        ppValues[i] = (int*)malloc(sizeof(int) * (n + 1));
        if (ppValues[i] != NULL) {
            memset(ppValues[i], 0, sizeof(int) * (n + 1));
        }
        else {
            return ret;
        }
    }
    
    for (int i=0; i <= m; i++) {
        for (int j=0; j <= n; j++) {
            if (i == 0)
                ppValues[i][j] = j;
            else if (j == 0)
                ppValues[i][j] = i;
            else if (string1[i-1] == string2[j-1])
                ppValues[i][j] = ppValues[i-1][j-1];
            else
                ppValues[i][j] = 1 + min3(ppValues[i-1][j],
                                         ppValues[i][j-1],
                                         ppValues[i-1][j-1]);
        }
    }
    
    ret = ppValues[m][n];

    for(int i = 0; i < m + 1; i++) {
        free( ppValues[i] );
    }
    free(ppValues);
    
    return ret;
}

char* getEDString(char *string1, char *string2, int m, int n, int **ppValues, int edLength) {
    char *pResult = NULL;
    int pos = edLength, y = m, x = n;
    if (edLength <= 0)
        return pResult;
    pResult = malloc(sizeof(char) * (edLength + 1));
    if (pResult != NULL) {
        memset(pResult, 0, sizeof(char) * (edLength + 1));
        while(pos > 0) {
            if (ppValues[y][x] > ppValues[y-1][x-1]) {
                pResult[pos-1] = string2[x-1];
                printf("(%d,%d) -> %c \n", y, x, string2[x-1]);
                y--;
                x--;
                pos--;
            }
            else if (ppValues[y][x] > ppValues[y][x-1]) {
                pResult[pos-1] = string2[x-1];
                printf("(%d,%d) x-> %c \n", y, x, string2[x-1]);
                x--;
                pos--;
            }
            else if (ppValues[y][x] > ppValues[y-1][x]) {
                pResult[pos-1] = ' ';//string1[y-1];
                printf("(%d,%d) y-> %c \n", y, x, string1[y-1]);
                y--;
                pos--;
            }
            else if (ppValues[y][x] == ppValues[y-1][x-1]) {
                printf("(%d,%d) -x-y \n", y, x);
                y--;
                x--;
            }
            else if (ppValues[y][x] == ppValues[y][x-1]) {
                printf("(%d,%d) -x \n", y, x);
                x--;
            }
            else if (ppValues[y][x] > ppValues[y-1][x]) {
                printf("(%d,%d) -y \n", y, x);
                y--;
            }
        }
    }
    
    return pResult;
}

int  ED_DP_print(char *string1, char *string2, int m, int n )
//int  ED_DP(char *string1, char *string2, int m, int n )
{
    int ret = 0;
    if (m == 0 || n == 0)
        return 0;
    
    int **ppValues = NULL;
    ppValues = (int**)malloc(sizeof(int*) * (m + 1));
    if (ppValues == NULL) {
        return ret;
    }
    for(int i = 0; i < m + 1; i++) {
        ppValues[i] = (int*)malloc(sizeof(int) * (n + 1));
        if (ppValues[i] != NULL) {
            memset(ppValues[i], 0, sizeof(int) * (n + 1));
        }
        else {
            return ret;
        }
    }
    
    for (int i=0; i <= m; i++) {
        for (int j=0; j <= n; j++) {
            // If first string is empty, only option is to
            // isnert all characters of second string
            if (i == 0)
                ppValues[i][j] = j;  // Min. operations = j
            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j == 0)
                ppValues[i][j] = i; // Min. operations = i
            else if (string1[i-1] == string2[j-1])
                ppValues[i][j] = ppValues[i-1][j-1];
            else
                ppValues[i][j] = 1 + min3(ppValues[i-1][j],
                                         ppValues[i][j-1],
                                         ppValues[i-1][j-1]);
        }
    }
    
    ret = ppValues[m][n];
    
    for (int j = 1; j <= n; j++) {
        printf("\t%c", string2[j-1]);
    }
    printf("\n");
    for (int i = 1; i <= m; i++) {
        printf("%c", string1[i-1]);
        for (int j = 1; j <= n; j++) {
            printf("\t%d", ppValues[i][j]);
        }
        printf("\n");
    }
    
    char *pResult = getEDString(string1, string2, m, n, ppValues, ret); //(char*)malloc(sizeof(char) * (ret + 1));
    if (pResult != NULL) {
        printf("문자열: [%s]\n", pResult);
        free(pResult);
    }
    
    for(int i = 0; i < m + 1; i++) {
        free( ppValues[i] );
    }
    free(ppValues);
    
    return ret;
}


