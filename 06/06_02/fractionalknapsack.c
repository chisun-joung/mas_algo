#include "fractionalknapsack.h"

int compare_KnapsackItem_ratio(const void *value1, const void *value2){
    KnapsackItem *item1 = (KnapsackItem*)value1;
    KnapsackItem *item2 = (KnapsackItem*)value2;
    
    double ratio1 = item1->profit / item1->weight;
    double ratio2 = item2->profit / item2->weight;
    
    if (ratio1 < ratio2) {
        return 1;
    }
    else if (ratio1 > ratio2) {
        return -1;
    }
    else {
        return 0;
    }
}

double fractionalKnapsack(double capacity, KnapsackItem *items, int item_count) {
    double max_profit = 0, current_weight = 0;
    int i =0;
    
    qsort(items, item_count, sizeof(KnapsackItem), compare_KnapsackItem_ratio);
    
    printf("정렬 결과\n\t무게\t가치\t비율\n");
    for (i = 0; i < item_count; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n", i, items[i].weight, items[i].profit,
               items[i].profit / items[i].weight);
    }
    
    for (i = 0; i < item_count; i++) {
        if(current_weight + items[i].weight < capacity) {
            items[i].selected = items[i].weight;
            current_weight = current_weight + items[i].weight ;
            max_profit += items[i].profit;
        }
        else {
            double remaining  = capacity - current_weight;
            items[i].selected = remaining;
            max_profit += items[i].profit * items[i].selected / items[i].weight;
            break;
        }
    }
    
    return max_profit;
}

void inputItems(KnapsackItem *items, int item_count) {
    int i = 0;
    for (i = 0; i < item_count; i++) {
        printf("%d 번째 물건의 이름을 입력해 주세요\n", i + 1);
        scanf("%s", items[i].name);
        
        printf("%d 번째 물건의 무게와 가치를 입력해 주세요\n", i + 1);
        scanf("%lf %lf", &items[i].weight, &items[i].profit);
        
        items[i].selected = 0;
    }
}

void printResult(KnapsackItem *items, int item_count, double max_profit) {
    int i = 0;
    printf("최대 이익: %.2f\n", max_profit);
    printf("(선택된 무게)\t(전체 무게)\n");
    for (i = 0; i < item_count; i++) {
        printf("%s\t%.2f\t%.2f\n", items[i].name, items[i].selected, items[i].weight);
    }
}
