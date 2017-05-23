#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"

void printArray(int value[], int count);

int main(int argc, char *argv[])
{
    int values[] = { 80, 75, 10, 60, 15, 49, 12, 25 };
    int count = sizeof(values)/sizeof(int);
    
    printf("선택 정렬 실행 전 \n");
    printArray(values, count);
    
    printf("\n선택 정렬이 시작됩니다 \n");
    slectionSort(values, count);
    
    printf("\n선택 정렬 결과 \n");
    printArray(values, count);
    
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
