#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct GraphEdgeInfoType
{
    int key;
    int fromNodeID;
    int toNodeID;
} GraphEdgeInfo;

typedef struct HeapNodeType
{
    GraphEdgeInfo data;
} HeapNode;

typedef struct ArrayHeapType
{
    int maxCount;           // 최대 노드 개수
    int currentCount;       // 현재 노드 개수
    HeapNode *pData;		// 노드 저장을 위한 1차원 array
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* createArrayMaxHeap(int maxCount);
int insertMaxHeapAH(ArrayMaxHeap* pHeap, GraphEdgeInfo value);
HeapNode* deleteMaxHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayMaxHeap(ArrayMaxHeap* pHeap);

ArrayMaxHeap* createArrayMinHeap(int maxCount);
int insertMinHeapAH(ArrayMaxHeap* pHeap, GraphEdgeInfo value);
HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayMinHeap(ArrayMaxHeap* pHeap);

void displayArrayHeap(ArrayMaxHeap* pHeap);

#endif
