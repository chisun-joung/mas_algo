#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "linkedgraph.h"
#include "single_source_sp.h"

// 다이크스트라(Dijkstra) 알고리즘
int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID) {
	int *pDistance = NULL;

    int *pS = NULL;
    int nodeCount = 0, i = 0;
	int vNodeID = 0, y_w = 0, y_v = 0;

    LinkedList      *pEdgeList = NULL;
	LinkedListNode  *pEdgeNode = NULL;
    GraphEdge       *pEdge = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pDistance;
	}

    nodeCount = pGraph->nodeCount;
	pDistance = (int *)malloc(sizeof(int) * nodeCount);
	pS = (int *)malloc(sizeof(int) * nodeCount);

    // 메모리 할당 성공 여부 확인.
    if (NULL == pDistance || NULL == pS) {
		if (pDistance != NULL) free(pDistance);
		printf("오류, 메모리 할당 in shortestPathDijkstra()\n");
		return NULL;
	}

    printf("Step-0. 초기화\n");
	for(i = 0; i < nodeCount; i++) {
        pS[i] = 1;
        pEdge = getEdgeLG(pGraph, sourceNodeID, i);
        if (NULL != pEdge) {
            pDistance[i] = pEdge->weight;
        }
        else {
            pDistance[i] = MAX_INT;
        }
	}
    pDistance[sourceNodeID] = 0;
    pS[sourceNodeID] = 0;
 
    printDistanceInfo(sourceNodeID, pDistance, nodeCount);

	for(i = 0; i < nodeCount - 1; i++) {
		printf("\n[%d]번째 루프\n", i+1);

		// Step-1.
		// 집합 S중 최단 거리를 가지는 노드(vNodeID)를 선택.
		vNodeID = getMinDistance(pDistance, pS, nodeCount);
		pS[vNodeID] = 0;
	
		// 선택된 노드(vNodeID)에 인접한 노드(wNodeID)에 대해 거리 변경 조건을 점검.
		pEdgeList = pGraph->ppAdjEdge[vNodeID];
		pEdgeNode = pEdgeList->headerNode.pLink;
		while(pEdgeNode != NULL) {
            int wNodeID = pEdgeNode->data.toNodeID;
            int c_v_w = pEdgeNode->data.weight;
            
			// y_v + c_v,w 와 y_w 비교
			y_v = pDistance[vNodeID];
			y_w = pDistance[wNodeID];
			if (y_v + c_v_w < y_w) {
				pDistance[wNodeID] = y_v + c_v_w;
                printf("\t[%d]노드의 이전 노드는 [%d]로 변경,거리는 [%d]에서 [%d](으)로 감소함\n",
                        wNodeID, vNodeID, y_w, y_v + c_v_w);
			}
			pEdgeNode = pEdgeNode->pLink;
		}
        printDistanceInfo(sourceNodeID, pDistance, nodeCount);
	}
	free(pS);
	
	return pDistance;
}

int getMinDistance(int* distance, int *pS, int nodeCount) {
	int pReturn = 0;
	int min_distance = MAX_INT;
	int i = 0;

	for(i = 0; i < nodeCount; i++) {
		if (0 != pS[i] && distance[i] < min_distance) {
			min_distance = distance[i];
			pReturn = i;
		}
	}

	return pReturn;
}

void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount) {
    int i = 0;
    
    for(i = 0; i < nodeCount; i++) {
        printf("\t[%d]부터 [%d]까지 거리: %d\n", sourceNodeID, i, pDistance[i]);
    }
}
