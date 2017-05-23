#include "tspbacktracking.h"

void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost) {
    for (int i = 0; i <= step; i++) {
        if (i > 0) {
            printf(" -(%d)-> ", pGraph[pPath[i-1]][pPath[i]]);
        }
        printf("%c", 'A' + pPath[i]);
    }
    printf("\t비용: %d\n", cost);
}

int checkValidPath(int pPath[], int step) {
    // 새로 추가된 step번째 도시가 이미 방문한 노드인지 점검한다.
    for (int i = 0; i < step; i++) {
        if (pPath[i] == pPath[step]) {
            return 0;
        }
    }
    return 1;
}

void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[], 
                      int pOptimalPath[], int* pMinCost) {
    int next_node = 0, current_node = 0, total_cost = 0;
    if (checkValidPath(pPath, step)) {
        current_node = pPath[step];
        
        if (step == NUM_OF_NODE - 1) {  // 마지막 노드인 경우.
            next_node = pPath[0];        // 다음 노드는 시작 노드임.
            pPath[step + 1] = next_node;
            total_cost = cost + pGraph[current_node][next_node];
            if (total_cost < *pMinCost) {   // 지금 구한 해가 기존 최적해보다 더 좋은 경우.
                *pMinCost = total_cost;     // 최적해를 변경시킨다.
                memcpy(pOptimalPath, pPath, sizeof(int) * NUM_OF_NODE);
                
                printf("*");                // 최적해의 변경을 표시.
            }
            printPath(pGraph, pPath, NUM_OF_NODE, total_cost);
        } else {
            for (int toNode = 1; toNode < NUM_OF_NODE; toNode++) {
                next_node = toNode;
                pPath[step + 1] = next_node;
                total_cost = cost + pGraph[current_node][next_node];
                TSP_BackTracking(pGraph, step + 1, total_cost, pPath,
                                 pOptimalPath, pMinCost);
            }
        }
    }
}
