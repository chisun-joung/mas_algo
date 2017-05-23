#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph.h"
#include "linkedstack.h"

#include "mst_prim.h"

// Prim 알고리즘
LinkedGraph* mstPrim(LinkedGraph* pGraph, int startNodeID)
{
	LinkedGraph*    pReturn = NULL;
    int             *pSelected = NULL;

	int             i = 0, nodeCount = 0;
	int             mstNodeCount = 0;
	int             fromNodeID = 0;
	PrimGraphEdge   minWeightEdge = {0,};

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	nodeCount = pGraph->nodeCount;
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, nodeCount);
    pSelected = (int*) malloc(sizeof(int) * nodeCount);
    if (NULL == pReturn || NULL == pSelected) {
        return NULL;
    }
    memset(pSelected, 0, sizeof(int) * nodeCount);
    
    pSelected[startNodeID] = 1;
    mstNodeCount = 1;

	while(mstNodeCount < nodeCount) {
		minWeightEdge.fromNodeID = 0;
		minWeightEdge.toNodeID = 0;
		minWeightEdge.weight = MAX_INT;

		for(i = 0; i < nodeCount; i++) {
			if (pSelected[i] == 1) {
				fromNodeID = i;
				getMinWeightEdge(pGraph, pReturn, fromNodeID, &minWeightEdge);
			}
		}
        addEdgeLG(pReturn, minWeightEdge.fromNodeID,
				minWeightEdge.toNodeID, minWeightEdge.weight);
        pSelected[minWeightEdge.toNodeID] = 1;
        mstNodeCount++;

        printf("[%d], 최소 가중치: (%d,%d)->%d, 노드 %d 추가\n",
               mstNodeCount, minWeightEdge.fromNodeID, minWeightEdge.toNodeID,
               minWeightEdge.weight, minWeightEdge.toNodeID);
	}

	return pReturn;
}

int checkEdge(LinkedGraph* pGraph, int fromNodeID, int toNodeID) {
    int             ret = 0;
    LinkedList      *pEdgeList = NULL;
    LinkedListNode  *pEdgeNode = NULL;
    
    if (pGraph != NULL) {
        pEdgeList = pGraph->ppAdjEdge[fromNodeID];
        if (pEdgeList != NULL) {
            pEdgeNode = pEdgeList->headerNode.pLink;
            while(pEdgeNode != NULL) {
                if (pEdgeNode->data.toNodeID == toNodeID) {
                    ret = 1;
                    break;
                }
                
                pEdgeNode = pEdgeNode->pLink;
            }
        }
    }
    
    return ret;
}


// 정점(fromNodeID)과 연결된 간선들 중,
// 가중치가 가장 작으면서 순환을 발생시키지 않는 간선을 선택.
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
					int fromNodeID, PrimGraphEdge *pMinWeightEdge) {
	LinkedListNode  *pListNode = NULL;
	int             isCycle = 0;
	int             isAlready = 0;
	LinkedList      *pEdgeList = pGraph->ppAdjEdge[fromNodeID];

	// pListNode: V(T)에 부속된 간선들 중 하나를 선택.
	pListNode = pEdgeList->headerNode.pLink;
	while(pListNode != NULL) {
		int toNodeID = pListNode->data.toNodeID;
		int weight = pListNode->data.weight;

		// 최소값인지 점검.
		if (pListNode->data.weight < pMinWeightEdge->weight) {
			// 기존의 E(T)에 속한 간선인지 점검
			isAlready = checkEdge(pMST, fromNodeID, toNodeID);
			if (0 == isAlready) {
				// 순환을 발생시키는지 점검
				isCycle = checkCycle(pMST, fromNodeID, toNodeID);
                if (0 != isCycle) {
                    printf("순환 발생: (%d,%d)->%d, Skip\n",
                           fromNodeID,
                           toNodeID, pListNode->data.weight);
                }
			}
			// 기존에 이미 E(T)에 속한 간선이 아니면서,
			// 순환을 발생시키지 않는,
			// 최소 가중치 간선을 선택.
			if (isAlready == 0 && isCycle == 0) {
				pMinWeightEdge->fromNodeID = fromNodeID;
				pMinWeightEdge->toNodeID = toNodeID;
				pMinWeightEdge->weight = weight;
			}
		}

		pListNode = pListNode->pLink;
	}
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
