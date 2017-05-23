#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph.h"
#include "linkedstack.h"
#include "grapharrayheap.h"
#include "mst_kruskal.h"

// 기존 그래프 G의 간선을 가중치 값에 따라 오름차순으로 정렬.
ArrayMinHeap *orderEdges(LinkedGraph* pGraph);

// 순환 발생 검사.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

LinkedGraph* mstKruskal(LinkedGraph* pGraph)
{
	LinkedGraph* pReturn = NULL;
    int i = 0, isCycle = 0, currentEdgeCount = 0;
    int edgeCount = 0;
	ArrayMinHeap    *pMinHeap = NULL;
	HeapNode        *pHeapNode = NULL;
    int             *pVisited = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}

	edgeCount = pGraph->edgeCount;
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, pGraph->nodeCount);
    pVisited = (int*) malloc(sizeof(int) * pGraph->nodeCount);
	if (NULL == pReturn || NULL == pVisited) {
		return NULL;
	}
    memset(pVisited, 0, sizeof(int) * pGraph->nodeCount);
    
	pMinHeap = orderEdges(pGraph);
	if (pMinHeap == NULL) {
		return NULL;
	}
	for(i = 0; i < edgeCount; i++) {
		pHeapNode = deleteMinHeapAH(pMinHeap);
		if (pHeapNode != NULL) {
			isCycle = checkCycle(pReturn, pHeapNode->data.fromNodeID,
								pHeapNode->data.toNodeID);
			if (isCycle != 0) {
                printf("[%d], 순환 발생: (%d,%d)->%d, Skip\n",
                       i, pHeapNode->data.fromNodeID,
                       pHeapNode->data.toNodeID, pHeapNode->data.key);
                free(pHeapNode);
                continue;
            }
            addEdgeLG(pReturn, pHeapNode->data.fromNodeID,
                    pHeapNode->data.toNodeID, pHeapNode->data.key);
            printf("[%d], 최소 가중치: (%d,%d)->%d\n",
                    i, pHeapNode->data.fromNodeID,
                    pHeapNode->data.toNodeID, pHeapNode->data.key);

            if (0 == pVisited[pHeapNode->data.fromNodeID]) {
                pVisited[pHeapNode->data.fromNodeID] = 1;
            }
            if (0 == pVisited[pHeapNode->data.toNodeID]) {
                pVisited[pHeapNode->data.toNodeID] = 1;
            }
            currentEdgeCount++;
			free(pHeapNode);

			if ((pReturn->nodeCount - 1) == currentEdgeCount) {
				break;
			}
		}
	}
    if (NULL != pVisited) {
        free(pVisited);
    }

	return pReturn;
}

ArrayMinHeap *orderEdges(LinkedGraph* pGraph) {
	int i = 0;
	int edgeCount = 0;
	ArrayMinHeap *pReturn = NULL;
	LinkedListNode *pListNode = NULL;
	LinkedList* pEdgeList = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	edgeCount = pGraph->edgeCount;
	if (edgeCount == 0) {
		printf("오류, 간선 개수가 0개\n");
		return pReturn;
	}

	pReturn = createArrayMinHeap(edgeCount);
	if (pReturn == NULL) {
		return pReturn;
	}

	for(i = 0; i < pGraph->nodeCount; i++) {
        {
			pEdgeList = pGraph->ppAdjEdge[i];
			pListNode = pEdgeList->headerNode.pLink;
			while(pListNode != NULL) {
				int vertexID = pListNode->data.toNodeID;
				int weight = pListNode->data.weight;

				// 무방향 그래프라면, 동일한 간선이 2개 리턴되므로,
				// 시작 노드 id가 종료 노드 id보다 작은 경우만 리턴되도록 한다.
				// 즉, 간선 1개만 리턴되도록 한다.
				if (pGraph->graphType == LINKED_GRAPH_TYPE_DIRECT
					|| (pGraph->graphType == LINKED_GRAPH_TYPE_UNDIRECT && i < vertexID)) {
					GraphEdgeInfo edgeInfo = {0,};
					edgeInfo.fromNodeID = i;
					edgeInfo.toNodeID = vertexID;
					edgeInfo.key = weight;
					insertMinHeapAH(pReturn, edgeInfo);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	return pReturn;
}


// 간선 추가로 인해 순환이 발생하는 지 검사.
// 기존에 경로가 있었다면, 순환이 발생한다.
// 기존의 깊이우선탐색(DFS)를 사용.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID)
{
	int pReturn = 0;

	int i = 0;
	int vertextID = 0;
	LinkedStack* pStack = NULL;
	LinkedStackNode* pStackNode = NULL;
	LinkedListNode *pListNode = NULL;
	int *pVisited = NULL;

	if (pGraph == NULL) {
		return pReturn;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		return pReturn;
	}

	pVisited = (int*) malloc(sizeof(int) * pGraph->nodeCount);
	if (pVisited == NULL) {
		printf("Error, malloc() in traversalDFS()\n");
		deleteLinkedStack(pStack);
		return pReturn;
	}

	// 초기화.
	for(i = 0; i < pGraph->nodeCount; i++) {
		pVisited[i] = 0;
	}
	
	pVisited[fromNodeID] = 1;
	pushLS(pStack, fromNodeID);

	while(isLinkedStackEmpty(pStack) == 0) {
		pStackNode = popLS(pStack);
		if (pStackNode != NULL) {
			vertextID = pStackNode->data;
			if (vertextID == toNodeID) {
				//printf("(%d,%d)-기존에 경로가 존재합니다.\n",
				//		fromNodeID, toNodeID);
				pReturn = 1;
				break;
			}

			pListNode = pGraph->ppAdjEdge[vertextID]->headerNode.pLink;
			while(pListNode != NULL) {
				int vertexID = pListNode->data.toNodeID;
				if (pVisited[vertexID] == 0) {
					pVisited[vertexID] = 1;
					pushLS(pStack, vertexID);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	free(pVisited);
	deleteLinkedStack(pStack);

	return pReturn;
}
