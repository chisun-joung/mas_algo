#include "coinchange.h"

int compare_CoinItem_value(const void *value1, const void *value2) {
    CoinItem *item1 = (CoinItem*)value1;
    CoinItem *item2 = (CoinItem*)value2;
    
    if (item1->value < item2->value) {
        return 1;
    }
    else if (item1->value > item2->value) {
        return -1;
    }
    else {
        return 0;
    }
}

int getChangeCount(int target_change, int coin_value) {
    int count = 0;
    
    if (target_change >= coin_value) {
        count = target_change / coin_value;
    }
    
    return count;
}

int getChange(int change_total, CoinItem *items, int item_count) {
    int current_change = change_total;
    int i =0;
    
    qsort(items, item_count, sizeof(CoinItem), compare_CoinItem_value);
    
    printf("정렬 결과\n\t값\n");
    for (i = 0; i < item_count; i++) {
        printf("%d\t%d\n", i, items[i].value);
    }
    
    for (i = 0; i < item_count; i++) {
        int count = getChangeCount(current_change, items[i].value);
        items[i].selected = count;
        current_change = current_change - count * items[i].value;
    }
    
    return current_change;
}

void inputItems(CoinItem *items, int item_count) {
    int i = 0;
    for (i = 0; i < item_count; i++) {
        printf("%d 번째 동전의 단위를 입력해 주세요 (예, 100)\n", i + 1);
        scanf("%d", &items[i].value);
        
        items[i].selected = 0;
    }
}

void printResult(CoinItem *items, int item_count, int remained) {
    int i = 0;
    printf("(동전)\t(동전 개수)\n");
    for (i = 0; i < item_count; i++) {
        printf("%d\t%d\n", items[i].value, items[i].selected);
    }
    printf("남은 거스름돈: %d\n", remained);
}

