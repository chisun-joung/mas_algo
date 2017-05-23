#include "coinchange_dp.h"

int getChange_Recursive(int change_total, CoinItem *items, int item_count) {
    int k = 0;
    int min = 99999;
    int value = 0;
    
    if (change_total <= 0)
        return 0;
    
    for (k = 0; k < item_count; k++) {
        if (change_total >= items[k].value) {
            value = getChange_Recursive(change_total - items[k].value, items, item_count) + 1;
            if (value < min) {
                min = value;
            }
        }
        //printf("change_total: %d, k: %d, value: %d,(%d => %d)\n", change_total, k, value,
        //       items[k].value, items[k].selected);
    }
    return min;
}

int getChange_DP(int change_total, CoinItem *items, int item_count) {
    
    int min = 0;
    int *pTotalCount = NULL;
    
    pTotalCount = (int*)malloc(sizeof(int) * (change_total+1));
    if (pTotalCount == NULL) {
        return min;
    }
    memset(pTotalCount, 0, sizeof(int) * item_count);
    
    for( int i = 1; i <= change_total; i++) {
        min = 9999;
        for (int j = 0; j < item_count; j++) {
            if (items[j].value <= i) {
                if (min > pTotalCount[i - items[j].value] + 1) {
                    min = pTotalCount[i - items[j].value] + 1;
                }
            }
        }
        pTotalCount[i] = min;
    }
    
    min = pTotalCount[change_total];

    free(pTotalCount);
    
    return min;
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


