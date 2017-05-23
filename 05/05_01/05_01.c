#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph.h"
#include "single_source_sp.h"

int main(int argc, char *argv[])
{
	LinkedGraph *pG = NULL;
	int *pResult = NULL;
    int i = 0;

	// 그래프 생성
	pG = createLinkedGraph(LINKED_GRAPH_TYPE_DIRECT, 6);
	if (pG != NULL) {
		// 그래프 초기화: 간선 추가
		addEdgeLG(pG, 0, 1, 2);
        addEdgeLG(pG, 0, 2, 4);
        addEdgeLG(pG, 2, 0, 4);
		addEdgeLG(pG, 1, 2, 1);
		addEdgeLG(pG, 2, 3, 7);
        addEdgeLG(pG, 3, 2, 5);
        addEdgeLG(pG, 3, 4, 2);
		addEdgeLG(pG, 3, 5, 6);
        addEdgeLG(pG, 4, 5, 3);
        addEdgeLG(pG, 5, 3, 6);
        
		printf("G3:\n");
		displayGraphLG(pG);

		printf("\n다이크스트라(Dijkstra) 알고리즘: \n");
		pResult = shortestPathDijkstra(pG, 0);  // 시작 노드: 0
        if (NULL != pResult) {
            printf("\n결과:\n");
            for(i = 0; i < pG->nodeCount; i++) {
                printf("%d 노드부터 %d 노드까지 걸리는 최단 거리: %d \n", 0, i, pResult[i]);
            }
			free(pResult);
		}
		deleteGraphLG(pG);
	}

	return 0;
}
