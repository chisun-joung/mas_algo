#ifndef _BTREE_DEF_
#define _BTREE_DEF_

#define BTREE_ORDER		5

typedef struct BTreeNodeDataType
{
	int key;
	char value;
} BTreeNodeData;

typedef struct BTreeNodeType
{
	int                     count;
	BTreeNodeData           data[BTREE_ORDER];
	struct BTreeNodeType*   children[BTREE_ORDER+1];
} BTreeNode;

#endif
