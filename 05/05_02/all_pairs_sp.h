#ifndef _GRAPH_ALL_PAIRS_SP_
#define _GRAPH_ALL_PAIRS_SP_

#define		MAX_INT		99999

// Floyd 알고리즘
int** shortestPathFloyd(LinkedGraph* pGraph);
void printMatrix(int **ppDistance, int nodeCount);

#endif
