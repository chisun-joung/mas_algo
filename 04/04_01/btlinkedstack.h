#ifndef _LINKED_STACK_
#define _LINKED_STACK_

typedef struct LinkedStackNodeType
{
	struct BTreeNodeType* data;
	struct LinkedStackNodeType* pLink;
} LinkedStackNode;

typedef struct LinkedStackType
{
	int currentCount;           // 현재 원소의 개수
	LinkedStackNode* pTop;      // Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, struct BTreeNodeType* data);
LinkedStackNode* popLS(LinkedStack* pStack);
LinkedStackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);

#endif
