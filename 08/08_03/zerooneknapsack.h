#ifndef zerooneknapsack_h
#define zerooneknapsack_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _KnapsackItem {
    char name[100];
    int weight;
    double profit;
    int selected;
} KnapsackItem;

void inputItems(KnapsackItem *items, int item_count);
int zeroOneKnapsack_Recursive(double capacity, KnapsackItem *items, int item_count);
int zeroOneKnapsack_DP(int capacity, KnapsackItem *items, int item_count);
//void printResult(KnapsackItem *items, int item_count, double max_profit);

#endif
