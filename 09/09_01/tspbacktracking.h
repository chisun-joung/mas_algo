#ifndef tspbacktracking_h
#define tspbacktracking_h

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_NODE 4

void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost);
void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[], 
                      int pOptimalPath[], int* pMinCost);

#endif
