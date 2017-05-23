#include "arrayheap.h"

ArrayMaxHeap* createArrayHeap(int maxCount) {
    ArrayMaxHeap *pReturn = NULL;
    if (maxCount > 0) {
        pReturn = (ArrayMaxHeap *)malloc(sizeof(ArrayMaxHeap));
        pReturn->maxCount = maxCount;
        pReturn->currentCount = 0;
        pReturn->pData = (HeapNode *)malloc(sizeof(HeapNode) * (maxCount + 1));
        memset(pReturn->pData, 0, sizeof(HeapNode) * (maxCount+1));
    }
    else {
        printf("최대 원소 개수는 0보다 커야 합니다\n");
    }
    
    return pReturn;
}

int insertMinHeapAH(ArrayMaxHeap* pHeap, HeapNode value) {
    int i = 0;
    
    if (pHeap != NULL) {
        if (pHeap->currentCount ==  pHeap->maxCount) {
            printf("오류, 히프가 가득찼습니다[%d],insertMaxHeapAH()\n",
                   pHeap->maxCount);
            return 0;
        }
        
        pHeap->currentCount++;
        i =  pHeap->currentCount;
        while((i != 1) && (value.frequency < pHeap->pData[i/2].frequency)) {
            pHeap->pData[i] = pHeap->pData[i/2];
            i /= 2;
        }
        pHeap->pData[i] = value;
    }
    
    return i;
}

HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap) {
    HeapNode* pReturn = NULL;
    HeapNode* pTemp = NULL;
    int parent =1, child = 2;
    
    if (pHeap != NULL && pHeap->currentCount >  0) {
        pReturn = (HeapNode*)malloc(sizeof(HeapNode));
        if (pReturn == NULL) {
            printf("오류, 메모리 할당, deleteMaxHeapAH()\n");
            return NULL;
        }
        *pReturn = pHeap->pData[ 1 ];
        
        pTemp = &(pHeap->pData[ pHeap->currentCount ]);
        pHeap->currentCount--;
        
        while(child <= pHeap->currentCount) {
            if ((child < pHeap->currentCount)
                && pHeap->pData[ child ].frequency > pHeap->pData[ child+1 ].frequency) {
                child++;
            }
            if (pTemp->frequency <= pHeap->pData[ child ].frequency) {
                break;
            }
            
            pHeap->pData[ parent ] = pHeap->pData[ child ];
            parent = child;
            child *= 2;
        }// end-of-while
        pHeap->pData[ parent ] = *pTemp;
    }
    
    return pReturn;
}

void deleteArrayHeap(ArrayMaxHeap* pHeap) {
    if (pHeap != NULL) {
        if (pHeap->pData != NULL) {
            free(pHeap->pData);
        }
        free(pHeap);
    }
}

void displayArrayHeap(ArrayMaxHeap* pHeap) {
    int i = 0;
    if (pHeap != NULL) {
        for(i = 1; i <= pHeap->currentCount; i++) {
            printf("[%d],%d\n", i, pHeap->pData[i].frequency);
        }
    }
}
