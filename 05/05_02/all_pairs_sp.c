#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "linkedgraph.h"
#include "all_pairs_sp.h"

// 플로이드(Floyd) 알고리즘
int** shortestPathFloyd(LinkedGraph* pGraph) {
	int **ppDistance = NULL;
	int r = 0, s = 0, v = 0;
	int nodeCount = 0;
    GraphEdge       *pEdge = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}
	nodeCount = pGraph->nodeCount;

	ppDistance = (int **)malloc(sizeof(int*) * nodeCount);
	if (ppDistance == NULL) {
		printf("오류, 메모리할당(1) in shortestPathFloyd()\n");
		return NULL;
	}

	for(r = 0; r < nodeCount; r++) {
		ppDistance[r] = (int *)malloc(sizeof(int) * nodeCount);
		if (ppDistance[r] == NULL) {
			for(s = 0; s < r - 1; s++) {
				if (ppDistance[s] != NULL) free(ppDistance[s]);
			}
			if (ppDistance != NULL)  free(ppDistance);
			printf("오류, 메모리할당(2) in shortestPathFloyd()\n");
			return NULL;
		}
	}
	// 초기화. 배열 pReturn의 초기화
	for(r = 0; r < nodeCount; r++) {
		for(s = 0; s < nodeCount; s++) {
			if (r == s) {
				ppDistance[r][s] = 0;
			}
			else {
                pEdge = getEdgeLG(pGraph, r, s);
                if (NULL != pEdge) {
                    ppDistance[r][s] = pEdge->weight;
                }
                else {
                    ppDistance[r][s] = MAX_INT;
                }
			}
		}
	}
	printMatrix(ppDistance, nodeCount);

	// Step 1. 삼중 Loop
	for(v = 0; v < nodeCount; v++) {
		for(r = 0; r < nodeCount; r++) {
			for(s = 0; s < nodeCount; s++) {
				if (ppDistance[r][v] + ppDistance[v][s] < ppDistance[r][s]) {
					ppDistance[r][s] = ppDistance[r][v] + ppDistance[v][s];
				}
			}
		}
		printf("[%d]-루프\n", v+1);
		printMatrix(ppDistance, nodeCount);
	}

	return ppDistance;
}

void printMatrix(int **A, int nodeCount) {
	int r = 0;
	int s = 0;

	for(s = 0; s < nodeCount; s++) {
		printf("\t%d", s);
	}
	printf("\n");

	for(r = 0; r < nodeCount; r++) {
		printf("%d: ", r);
		for(s = 0; s < nodeCount; s++) {
			printf("\t%d", A[r][s]);
		}
		printf("\n");
	}
}


