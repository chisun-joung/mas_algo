#ifndef coinchange_h
#define coinchange_h

#include <stdio.h>
#include <stdlib.h>

typedef struct CoinItem {
    int value;
    int selected;
} CoinItem;

void inputItems(CoinItem *items, int item_count);
int getChange(int change_total, CoinItem *items, int item_count);
void printResult(CoinItem *items, int item_count, int remained);

#endif

