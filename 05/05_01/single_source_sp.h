#ifndef _GRAPH_SP_
#define _GRAPH_SP_

#define		MAX_INT		99999

// Dijkstra 알고리즘
int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID);
int getMinDistance(int* pDistance, int *pS, int nodeCount);
void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount);

#endif
