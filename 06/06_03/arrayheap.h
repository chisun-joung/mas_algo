#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType
{
    int frequency;
    void *pData;    //HuffmanTreeNode를 가리킴.
} HeapNode;

typedef struct ArrayHeapType
{
    int maxCount;           // 최대 노드 개수
    int currentCount;       // 현재 노드 개수
    HeapNode *pData;		// 노드 저장을 위한 1차원 array
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* createArrayHeap(int maxCount);
int insertMinHeapAH(ArrayMaxHeap* pHeap, HeapNode value);
HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayHeap(ArrayMaxHeap* pHeap);
void displayArrayHeap(ArrayMaxHeap* pHeap);

#endif
