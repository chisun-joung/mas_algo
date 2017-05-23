#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

// B-트리 생성
BTree* createBTree()
{
	BTree *pReturn = NULL;

	pReturn = (BTree *)malloc(sizeof(BTree));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree));
	}
	else {
		printf("오류, 메모리할당 in createBTree()\n");
		return NULL;
	}

	return pReturn;
}

BTreeNodeData* searchBT(BTree* pBTree, int key) 
{
	BTreeNodeData* pReturn = NULL;
	BTreeNode* pCurrentNode = NULL;
	int i = 0;

	if (pBTree != NULL) {
		pCurrentNode = pBTree->pRootNode;
		while(pCurrentNode != NULL)	{
			for (i = 0; i < pCurrentNode->count; i++) {
				int currentKey = pCurrentNode->data[i].key;
				if (key == currentKey) {
					pReturn = &pCurrentNode->data[i];
					return pReturn;
				}
				else if (key < currentKey) {
					break;
				}
			}
			pCurrentNode = pCurrentNode->children[i];
		}
	}

	return pReturn;
}

// 자료 추가.
int addDataBT(BTree* pBTree, BTreeNodeData data)
{
	int ret = 1;
	int i = 0;
	BTreeNode *pParentNode = NULL, *pCurrentNode = NULL;
	LinkedStack* pStack = NULL;

	if (pBTree == NULL) {
		ret = 0;
		return ret;
	}
	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = 0;
		return ret;
	}
	// INSERT할 leaf node 찾기.
	pCurrentNode = pBTree->pRootNode;
	while(pCurrentNode != NULL) {
		pushLS(pStack, pCurrentNode);
        pParentNode = pCurrentNode;
        
		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (data.key == currentKey) {
				printf("오류,중복된 키-[%d]\n", data.key);
				ret = 0;
				deleteLinkedStack(pStack);
				return ret;
			}
			else if (data.key < currentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->children[i];
	}
	if (pParentNode == NULL) {	// ROOT 노드가 아직 없는 경우.
		pBTree->pRootNode = createBTreeNode(data);
	}
	else {
		addNodeBT(pParentNode, data, NULL);

		splitNodeBT(pBTree, pStack);
	}
	ret = 1;
	deleteLinkedStack(pStack);

	return ret;
}

void splitNodeBT(BTree* pBTree, LinkedStack* pStack)
{
	LinkedStackNode* pParentStackNode = NULL;
	LinkedStackNode* pCurrentStackNode = NULL;

	BTreeNode* pCurrentBTreeNode = NULL;
	BTreeNode* pNewBTreeNode = NULL;
	BTreeNodeData pivotElement = {0,};
	int pivotIndex = BTREE_ORDER / 2;
	int i = 0;

	if (pStack == NULL) {
		return;
	}
	pCurrentStackNode = popLS(pStack);
	while(pCurrentStackNode != NULL) {
		pCurrentBTreeNode =  pCurrentStackNode->data;
		if (pCurrentBTreeNode->count >= BTREE_ORDER) {
			pNewBTreeNode = (BTreeNode *)malloc(sizeof(BTreeNode));
			if (pNewBTreeNode != NULL) {
				memset(pNewBTreeNode, 0, sizeof(BTreeNode));
			}
			else {
				printf("Error, malloc() in splitNodeBT()\n");
				break;
			}

			pivotElement = pCurrentBTreeNode->data[pivotIndex];
			memset(&pCurrentBTreeNode->data[pivotIndex], 0, sizeof(BTreeNodeData));

			for(i = pivotIndex + 1; i < BTREE_ORDER; i++) {
				pNewBTreeNode->data[i - pivotIndex - 1] = pCurrentBTreeNode->data[i];
				pNewBTreeNode->children[i - pivotIndex - 1] = pCurrentBTreeNode->children[i];

				memset(&pCurrentBTreeNode->data[i], 0, sizeof(BTreeNodeData));
				pCurrentBTreeNode->children[i] = NULL;
			}
			pNewBTreeNode->children[i - pivotIndex - 1] = pCurrentBTreeNode->children[i];
			pCurrentBTreeNode->children[i] = NULL;
			pNewBTreeNode->count = BTREE_ORDER - pivotIndex - 1;
			pCurrentBTreeNode->count = pivotIndex;

			pParentStackNode = popLS(pStack);
			if (pParentStackNode != NULL) {
				addNodeBT(pParentStackNode->data, pivotElement, pNewBTreeNode);
			}
			else {
				// 트리 전체 Depth가 1증가.
				pBTree->pRootNode = createBTreeNode(pivotElement);
				pBTree->pRootNode->children[0] = pCurrentBTreeNode;
				pBTree->pRootNode->children[1] = pNewBTreeNode;
			}
		}
		
		if (pCurrentStackNode != NULL) {
			free(pCurrentStackNode);
		}
		pCurrentStackNode = pParentStackNode;
		pParentStackNode = NULL;
	}

	if (pCurrentStackNode != NULL) free(pCurrentStackNode);
	if (pParentStackNode != NULL) free(pParentStackNode);
}

BTreeNode* createBTreeNode(BTreeNodeData data)
{
	BTreeNode* pReturn = NULL;

	pReturn = (BTreeNode *)malloc(sizeof(BTreeNode));
	if (pReturn != NULL) {	// 메모리 할당 성공 검증
		// 데이터 초기화.
		memset(pReturn, 0, sizeof(BTreeNode));
		pReturn->data[0] = data;
		pReturn->count = 1;
	}
	else {
		printf("Error, malloc() in createBTreeNode()\n");
	}

	return pReturn;
}

void addNodeBT(BTreeNode* pCurrentNode, 
				BTreeNodeData data,
				BTreeNode* pRChildNode) {
	int i = 0;
	for(i = pCurrentNode->count - 1; i >= 0; i--) {
		int tempKey = pCurrentNode->data[i].key;
		if (data.key < tempKey) {
			pCurrentNode->data[i+1] = pCurrentNode->data[i];
			pCurrentNode->children[i+2] = pCurrentNode->children[i+1];
		}
		else {
			break;
		}
	}
	pCurrentNode->data[i+1] = data;
	pCurrentNode->children[i+2] = pRChildNode;
	pCurrentNode->count++;
}

// 자료 제거.
int removeDataBT(BTree* pBTree, int key)
{
	int ret = 1;
	int i = 0;
	int isFind = 0;

	BTreeNode* pParentNode = NULL;
	BTreeNode* pCurrentNode = NULL;

	LinkedStack* pStack = NULL;

	if (pBTree == NULL) {
		ret = 0;
		return ret;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = 0;
		return ret;
	}

	// 제거할 node 찾기.
	pCurrentNode = pBTree->pRootNode;
	while(pCurrentNode != NULL && isFind == 0) {
		pParentNode = pCurrentNode;
		pushLS(pStack, pParentNode);

		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (key == currentKey) {
				isFind = 1;
				break;
			}
			else if (key < currentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->children[i];
	}

	if (isFind == 1) {
		if (isLeafNode(pParentNode) == 0) {
			pParentNode = replaceLeafNodeBT(pBTree, pParentNode, i, pStack);
		}
		else {
			deleteKeyBT(pParentNode, i);
		}
		if (pParentNode->count < (BTREE_ORDER/2)) {
			balanceBTree(pBTree, pStack);
		}

		ret = 1;
	}
	else {
		ret = 0;
		printf("오류,검색키-[%d]가 발견되지 않습니다,removeDataBT()\n", key);

	}
	deleteLinkedStack(pStack);

	return ret;
}

void balanceBTree(BTree *pBTree, LinkedStack* pStack)
{
	LinkedStackNode* pParentStackNode = NULL;
	LinkedStackNode* pCurrentStackNode = NULL;
	BTreeNode* pParentBTreeNode = NULL;
	BTreeNode* pCurrentBTreeNode = NULL;

	int index = 0;

	if (pStack == NULL) {
		return;
	}
	pCurrentStackNode = popLS(pStack);
	if (pCurrentStackNode == NULL) {
		return;
	}

	pCurrentBTreeNode =  pCurrentStackNode->data;
	if (pCurrentBTreeNode->count >= (BTREE_ORDER/2)) {
		free(pCurrentStackNode);
		return;
	}

	pParentStackNode = popLS(pStack);
	if (pParentStackNode == NULL) {
		free(pCurrentStackNode);
		return;
	}

	pParentBTreeNode = pParentStackNode->data;
	index = getIndexInfo(pParentBTreeNode, pCurrentBTreeNode);

	// 오른쪽에서 빌려옴.
	if (index < pParentBTreeNode->count
		&& pParentBTreeNode->children[index+1]->count >= (BTREE_ORDER/2 + 1)) {
		borrowRightNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index+1]);
	// 왼쪽에서 빌려옴.
	} else if (index > 0
			&& pParentBTreeNode->children[index-1]->count >= (BTREE_ORDER/2 + 1)) {
		borrowLeftNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index-1]);
	}
	else {
		// 병합.
		mergeNodeBT(pBTree, pStack, pParentBTreeNode, pCurrentBTreeNode, index);
	}

	if (pCurrentStackNode != NULL) {
		free(pCurrentStackNode);
	}
	if (pParentStackNode != NULL) {
		free(pParentStackNode);
	}
}

void borrowRightNodeBT(BTreeNode* pParentNode, 
					 BTreeNode* pCurrentNode, int index, 
					 BTreeNode* pRightNode)
{
	int count = 0;

	if (pParentNode == NULL || pCurrentNode == NULL || pRightNode == NULL) {
		return;
	}

	// Parent 노드에서 자료 한 개 가져오기.
	count = pCurrentNode->count;
	pCurrentNode->data[count] = pParentNode->data[index];
	pCurrentNode->count++;

	// 오른쪽 노드의 가장 왼쪽 자료 가져오기.
	pParentNode->data[index] = pRightNode->data[0];

	// 오른쪽 노드 왼쪽으로 한칸씩 Shift.
	deleteKeyBT(pRightNode, 0);
}

void borrowLeftNodeBT(BTreeNode* pParentNode, 
					BTreeNode* pCurrentNode, int index, 
					BTreeNode* pLeftNode)
{
	int count = 0;
	BTreeNodeData leftElement = {0,};
	BTreeNodeData parentElement = {0,};

	if (pParentNode == NULL || pCurrentNode == NULL || pLeftNode == NULL) {
		return;
	}

	//왼쪽 노드의 가장 오른쪽 자료를 부모 노드로 이동.
	count = pLeftNode->count;
	leftElement = pLeftNode->data[count - 1];
	parentElement = pParentNode->data[index - 1];
	deleteKeyBT(pLeftNode, count - 1);

	pParentNode->data[index - 1] = leftElement;

	// Parent 노드의 자료를 오른쪽 노드의 가장 왼쪽으로 insert하기.
	addNodeBT(pCurrentNode, 
				parentElement,
				NULL);
}

void mergeNodeBT(BTree *pBTree, LinkedStack* pStack, 
				BTreeNode* pParentBTreeNode, 
				BTreeNode* pCurrentBTreeNode, int index)
{
	LinkedStackNode* pParentStackNode = NULL;
	BTreeNode* pParentParentNode = NULL;
	BTreeNode* pLeftNode = NULL;
	BTreeNode* pRightNode = NULL;
	BTreeNodeData parentElement = {0,};
	int i = 0;
	int pivotIndex = 0;

	if (pBTree == NULL || pStack == NULL 
		|| pParentBTreeNode == NULL || pCurrentBTreeNode == NULL) {
		return;
	}

	// 오른쪽 노드와 병합.
	if (index < pParentBTreeNode->count) {
		pLeftNode = pCurrentBTreeNode;
		pRightNode = pParentBTreeNode->children[index+1];
		pivotIndex = index;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}
	else {
		//왼쪽 노드와 병합.
		pLeftNode = pParentBTreeNode->children[index-1];
		pRightNode = pCurrentBTreeNode;
		pivotIndex = index-1;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}

	// 왼쪽 노드에 Parent 자료 추가.
	addNodeBT(pLeftNode, parentElement, pRightNode->children[0]);

	// 왼쪽 노드에 오른쪽 노드 자료들 추가.
	for(i = 0; i < pRightNode->count; i++) {
		addNodeBT(pLeftNode, pRightNode->data[i], pRightNode->children[i+1]);
	}
	deleteKeyBT(pParentBTreeNode, pivotIndex);
	free(pRightNode);

	if (pParentBTreeNode->count < (BTREE_ORDER/2)) {
		int index = 0;
		pParentStackNode = popLS(pStack);
		if (pParentStackNode != NULL) {
			pParentParentNode = pParentStackNode->data;
			index = getIndexInfo(pParentParentNode, pParentBTreeNode);

			//displayBTree(pBTree);

			mergeNodeBT(pBTree, pStack, 
					pParentParentNode, 
					pParentBTreeNode, index);

			free( pParentStackNode );
		}
		else {
			if (pParentBTreeNode->count == 0) {
				free( pBTree->pRootNode );
				pBTree->pRootNode = pLeftNode;
				//printf("LAST: %d, %c", pLeftNode->data[0].key, pLeftNode->data[0].value);
			}
		}
	}
}

BTreeNode* replaceLeafNodeBT(BTree *pBTree, BTreeNode* pDelNode, int index,
								LinkedStack* pStack)
{
	BTreeNode* pReturn = NULL;
	BTreeNodeData leafNodeElement = {0,};
	BTreeNode *pChildNode = NULL;
	BTreeNode* pParentNode = pDelNode;
	int count = index;

	if (pBTree == NULL || pDelNode == NULL) {
		return pReturn;
	}

	do {
		pChildNode = pParentNode->children[count];
		pushLS(pStack, pChildNode);

		count = pChildNode->count;
		pParentNode = pChildNode;
	}
	while(pChildNode->children[count] != NULL);

	leafNodeElement = pChildNode->data[count - 1];
	pDelNode->data[index] = leafNodeElement;
	deleteKeyBT(pChildNode, count - 1);

	pReturn = pChildNode;

	return pReturn;
}

int isLeafNode(BTreeNode* pParentNode)
{
	int ret = 0;

	if (pParentNode != NULL) {
		if (pParentNode->children[0] == NULL) {
			ret = 1;
		}
	}

	return ret;
}

int getIndexInfo(BTreeNode* pParentNode, BTreeNode* pCurrentNode)
{
	int ret = 0;
	int i = 0;

	if (pParentNode != NULL) {
		for(i = 0; i <= pParentNode->count; i++) {
			if (pParentNode->children[i] == pCurrentNode) {
				ret = i;
				break;
			}
		}
	}

	return ret;
}

void deleteKeyBT(BTreeNode* pNode, int index)
{
	int i = 0;
	if (pNode != NULL) {
		for(i = index + 1; i < pNode->count; i++) {
			pNode->data[i - 1] = pNode->data[i];
			pNode->children[i] = pNode->children[i+1];
		}
		memset(&pNode->data[pNode->count - 1], 0, sizeof(BTreeNodeData));
		pNode->children[pNode->count] = NULL;

		pNode->count--;
	}
}

// 트리 삭제.
void deleteBTree(BTree* pBTree)
{
    if (pBTree != NULL) {
        deleteBTreeNode(pBTree->pRootNode);
        free(pBTree);
    }
}

// 트리 노드의 삭제(재귀적).
void deleteBTreeNode(BTreeNode* pBTreeNode)
{
    int i = 0;
    if (pBTreeNode != NULL) {
        for(i = 0; i <= pBTreeNode->count; i++) {
            deleteBTreeNode(pBTreeNode->children[i]);
        }
        free(pBTreeNode);
    }
}

void displayBTree(BTree *pTree)
{
	if (pTree != NULL) {
		displayBTreeNode(pTree->pRootNode);
	}
}

void displayBTreeNode(BTreeNode *pNode)
{
    int i;
    static int x = 0;
	if (pNode != NULL) {
		x += 2;
		for (i = 2; i < x; i++) {
			printf("   ");
		}
		for (i = 0; i < pNode->count; i++) {
			printf("(%d,%c) ", pNode->data[i].key, pNode->data[i].value);
		}
		printf("\n");
		for (i = 0; i < pNode->count + 1; i++) {
			displayBTreeNode(pNode->children[i]);
		}
		x -= 2;
	}
}

