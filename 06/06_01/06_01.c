#include <stdio.h>
#include "coinchange.h"

int main() {
    CoinItem *items = NULL;
    
    int item_count = 0;
    int change_total = 0, remained = 0;
    
    printf("거스름돈은 얼마인가요?\n");
    scanf("%d", &change_total);
    
    printf("동전의 종류는 몇 가지인가요?\n");
    scanf("%d", &item_count);
    
    if (item_count > 0 && change_total > 0) {
        items = (CoinItem *)malloc(sizeof(CoinItem) * item_count);
        if (NULL != items) {
            inputItems(items, item_count);
            
            remained = getChange(change_total, items, item_count);
            
            printResult(items, item_count, remained);
            
            free(items);
        }
    }
    else {
        printf("용량과 물건의 개수는 0보다 커야 합니다\n");
    }
    
    return 0;
}
