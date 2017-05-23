#include "zerooneknapsack.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

int zeroOneKnapsack_Recursive(double capacity, KnapsackItem *items, int item_count) {
    if (item_count == 0 || capacity == 0)
        return 0;
    
    if (items[item_count - 1].weight > capacity)
        return zeroOneKnapsack_Recursive(capacity, items, item_count - 1);
    else
        return max( zeroOneKnapsack_Recursive(capacity, items, item_count - 1),
                   items[item_count - 1].profit
                    + zeroOneKnapsack_Recursive(capacity - items[item_count - 1].weight, items, item_count - 1));
}

int zeroOneKnapsack_DP(int capacity, KnapsackItem *items, int item_count) {
    int max_profit = 0;
    
    int **ppValues = NULL;
    
    if (capacity <= 0 || item_count <= 0)
        return max_profit;
    
    ppValues = (int**)malloc(sizeof(int*) * (item_count + 1));
    if (ppValues == NULL) {
        return max_profit;
    }
    for(int i = 0; i < item_count + 1; i++) {
        ppValues[i] = (int*)malloc(sizeof(int) * (capacity + 1));
        if (ppValues[i] != NULL) {
            memset(ppValues[i], 0, sizeof(int) * (capacity + 1));
        }
        else {
            return max_profit;
        }
    }
    
    for (int i = 0; i <= item_count; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                ppValues[i][w] = 0;
            else if (items[i - 1].weight <= w)
                ppValues[i][w] = max( items[i-1].profit
                                     + ppValues[i - 1][w - items[i-1].weight ],
                                     ppValues[i-1][w]);
            else
                ppValues[i][w] = ppValues[i-1][w];
        }
    }
    
    max_profit = ppValues[item_count][capacity];
    
    for(int i = 0; i < item_count + 1; i++) {
        free( ppValues[i] );
    }
    free(ppValues);
    
    return max_profit;
}

void inputItems(KnapsackItem *items, int item_count) {
    int i = 0;
    for (i = 0; i < item_count; i++) {
        printf("%d 번째 물건의 이름을 입력해 주세요\n", i + 1);
        scanf("%s", items[i].name);
        
        printf("%d 번째 물건의 무게와 가치를 입력해 주세요\n", i + 1);
        scanf("%d %lf", &items[i].weight, &items[i].profit);
        
        items[i].selected = 0;
    }
}

