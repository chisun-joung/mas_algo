#ifndef _GRAPH_MST_PRIM_
#define _GRAPH_MST_PRIM_

#define		MAX_INT		99999

typedef struct PrimGraphEdgeType
{
	int fromNodeID; // 시작 노드 ID
	int toNodeID;   // 종료 노드 ID
	int	weight;     // 가중치
} PrimGraphEdge;

// Prim 알고리즘
LinkedGraph *mstPrim(LinkedGraph* pGraph, int startNodeID);

// 노드(fromNodeID)과 연결된 간선들 중에서
// 가중치가 가장 작으면서 순환을 발생시키지 않는 간선을 선택.
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
                      int fromNodeID, PrimGraphEdge *pMinWeightEdge);

// 순환 검사.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

// 기존에 이미 있는 간선인지 검사.
int checkEdge(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

#endif
