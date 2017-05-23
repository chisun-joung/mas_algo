#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"

void printArrayForSelectionSort(int value[], int count);

void slectionSort(int value[], int count)
{
    int i = 0, j = 0;
    int min = 0, temp = 0;
    
    for(i = 0; i < count-1; i++) {
        min = i;
        for(j = i+1; j < count; j++) {
            if (value[j] < value[min]) {
                min  = j;
            }
        }
        temp = value[i];
        value[i] = value[min];
        value[min] = temp;
        
        printf("Step-%d,", i+1);
        printArrayForSelectionSort(value, count);
    }
}

void printArrayForSelectionSort(int value[], int count)
{
    int i = 0;
    for(i = 0; i < count; i++) {
        printf("%d ", value[i]);
    }
    printf("\n");
}

