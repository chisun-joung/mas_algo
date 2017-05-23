#include <stdio.h>
#include <stdlib.h>

#include "quickSort.h"

void printArrayForQuickSort(int value[], int start, int end)
{
    for(int i = start; i <= end; i++) {
        printf("%d ", value[i]);
    }
    printf("\n");
}

int partitionQuickSort(int value[], int start, int end)
{
    int pivot = end;
    int right = end;
    int left = start;
    int temp = 0;
    
    while(left < right) {
        while((value[left] < value[pivot]) && (left < right)) {
            left++;
        }
        while((value[right] >= value[pivot]) && (left < right)) {
            right--;
        }
        
        if (left < right) {
            printf("정렬 범위: %d~%d,피봇-[%d],Left(%d)-Right(%d) 교환 전,", start, end, value[pivot], value[left], value[right]);
            printArrayForQuickSort(value, start, end);

            temp = value[left];
            value[left] = value[right];
            value[right] = temp;

            printf("정렬 범위: %d~%d,피봇-[%d],교환 후,", start, end, value[pivot]);
            printArrayForQuickSort(value, start, end);
        }
    }
    printf("정렬 범위: %d~%d,피봇-[%d],피봇과 (%d) 교환 전,", start, end, value[pivot], value[right]);
    printArrayForQuickSort(value, start, end);
    
    temp = value[pivot];
    value[pivot] = value[right];
    value[right] = temp;
    
    printf("정렬 범위: %d~%d,피봇 교환 후,", start, end);
    printArrayForQuickSort(value, start, end);
    
    return right;
}

void quickSort(int value[], int start, int end)
{
    int pivot = 0;
    if (start < end) {
        pivot = partitionQuickSort(value, start, end);
        quickSort(value, start, pivot - 1);
        quickSort(value, pivot+1, end);
    }
}
