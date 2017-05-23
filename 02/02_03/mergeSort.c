#include <stdio.h>
#include <stdlib.h>

#include "mergeSort.h"

void printArrayForMergeSort(int value[], int start, int middle, int end)
{
    int t = 0;
    printf("정렬 범위: %d~%d,중간 위치-%d,", start, end, middle);
    for(t = start; t <= end; t++) {
        printf("%d ", value[t]);
    }
    printf("\n");
}

void mergeSortInternal(int value[], int buffer[], int start, int middle, int end)
{
    int i = 0, j = 0, k = 0, t = 0;
    i = start;
    j = middle + 1;
    k = start;
    
    while(i <= middle && j <= end) {
        if (value[i] <= value[j]) {
            buffer[k] = value[i];
            i++;
        }
        else {
            buffer[k] = value[j];
            j++;
        }
        k++;
    }
    
    if (i > middle) {
        for(t = j; t <= end; t++, k++) {
            buffer[k] = value[t];
        }
    }
    else {
        for(t = i; t <= middle; t++, k++) {
            buffer[k] = value[t];
        }
    }
    for(t = start; t <= end; t++) {
        value[t] = buffer[t];
    }
    
    printArrayForMergeSort(value, start, middle, end);
}

void mergeSort(int value[], int buffer[], int start, int end)
{
    int middle = 0;
    if (start < end) {
        middle = (start + end) / 2;
        mergeSort(value, buffer, start, middle);
        mergeSort(value, buffer, middle+1, end);
        mergeSortInternal(value, buffer, start, middle, end);
    }
}

