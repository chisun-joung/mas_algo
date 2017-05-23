#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph.h"
#include "mst_kruskal.h"

int main(int argc, char *argv[])
{
    LinkedGraph *pG3 = NULL;
    LinkedGraph *pMST1 = NULL;
    
    // 그래프 생성
    pG3 = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, 6);
    if (pG3 != NULL) {
        // 그래프 초기화: 간선 추가

        addEdgeLG(pG3, 0, 1, 4);
        addEdgeLG(pG3, 0, 2, 3);
        addEdgeLG(pG3, 1, 2, 2);
        addEdgeLG(pG3, 2, 3, 1);
        addEdgeLG(pG3, 3, 4, 1);
        addEdgeLG(pG3, 3, 5, 5);
        addEdgeLG(pG3, 4, 5, 6);

        printf("G3:\n");
        displayGraphLG(pG3);
        
        // Kruskal 알고리즘으로 MST 생성
        printf("\nKruskal MST:\n");
        pMST1 = mstKruskal(pG3);
        displayGraphLG(pMST1);
        
        // 그래프 삭제
        deleteGraphLG(pG3);
        deleteGraphLG(pMST1);
    }
    
    return 0;
}
