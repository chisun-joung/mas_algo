#ifndef _B_TREE_
#define _B_TREE_

#include "btreedef.h"
#include "btlinkedstack.h"

typedef struct BTreeType
{
	BTreeNode *pRootNode;
} BTree;

// B-트리 생성.
BTree* createBTree();

// B-트리 삭제.
void deleteBTree(BTree* pBTree);

// 검색.
BTreeNodeData* searchBT(BTree* pBTree, int key);

// 자료 추가.
int addDataBT(BTree* pBTree, BTreeNodeData data);

// 자료 제거.
int removeDataBT(BTree* pBTree, int key);

// B-트리 표시.
void displayBTree(BTree *pTree);


// 그외 내부 함수들.
BTreeNode* createBTreeNode(BTreeNodeData data);

void addNodeBT(BTreeNode* pCurrentNode,
				BTreeNodeData data,
				BTreeNode* pRChildNode);

void splitNodeBT(BTree* pBTree, LinkedStack* pStack);

int isLeafNode(BTreeNode* pParentNode);

BTreeNode* replaceLeafNodeBT(BTree *pBTree, BTreeNode* pDelNode, int index,
                LinkedStack* pStack);

void deleteBTreeNode(BTreeNode* pBTreeNode);

void deleteKeyBT(BTreeNode* pNode, int index);

void balanceBTree(BTree* pBTree, LinkedStack* pStack);

int getIndexInfo(BTreeNode* pParentNode, BTreeNode* pCurrentNode);

void borrowRightNodeBT(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
                int index, BTreeNode* pRightNode);

void borrowLeftNodeBT(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
                int index, BTreeNode* pLeftNode);

void mergeNodeBT(BTree *pBTree, LinkedStack* pStack, BTreeNode* pParentBTreeNode,
                BTreeNode* pCurrentBTreeNode, int index);

void displayBTreeNode(BTreeNode *pNode);

#endif

