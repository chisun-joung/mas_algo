#ifndef _LINKEDLIST_
#define _LINKEDLIST_

typedef struct GraphEdgeType {
    int toNodeID;		// 노드 ID
    int weight;			// 가중치.
} GraphEdge;

typedef struct LinkedListNodeType {
    GraphEdge data;
    struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType {
    LinkedListNode  headerNode;
    int             currentCount;
} LinkedList;

LinkedList *createLinkedList();
GraphEdge* getLinkedListData(LinkedList* pList, int position);
int addLinkedListData(LinkedList* pList, int position, GraphEdge data);
int removeLinkedListData(LinkedList* pList, int position);
void deleteLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);

#endif
