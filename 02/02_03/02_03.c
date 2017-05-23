#include <stdio.h>
#include <stdlib.h>

#include "mergeSort.h"

void printArray(int value[], int count);

int main(int argc, char *argv[])
{
    int values[] = { 80, 75, 10, 60, 15, 49, 12, 25 };
    int *pBuffer = NULL;
    
    printf("병합 정렬 실행 전 \n");
    printArray(values, 8);
    
    printf("\n병합 정렬이 시작됩니다 \n");
    pBuffer = (int *)malloc(sizeof(int) * 8);
    if (pBuffer != NULL) {
        mergeSort(values, pBuffer, 0, 7);
        
        free(pBuffer);
    }
    
    printf("\n병합 정렬 결과 \n");
    printArray(values, 8);
    
    return 0;
}

void printArray(int value[], int count)
{
    int i = 0;
    for(i = 0; i < count; i++) {
        printf("%d ", value[i]);
    }
    printf("\n");
}
