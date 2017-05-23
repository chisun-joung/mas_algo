#ifndef coinchange_dp_h
#define coinchange_dp_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct CoinItem {
    int value;
    int selected;
} CoinItem;

void inputItems(CoinItem *items, int item_count);
int getChange_Recursive(int change_total, CoinItem *items, int item_count);
int getChange_DP(int change_total, CoinItem *items, int item_count);
//void printResult(CoinItem *items, int item_count, int remained);

#endif

