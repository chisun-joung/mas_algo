#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

int main(int argc, char *argv[])
{
    BTree *pTree = NULL;
    BTreeNodeData *pSearchData = NULL;
    int key = 0;
    
    BTreeNodeData eA = {9, 'A'};
    BTreeNodeData eB = {12, 'B'};
    BTreeNodeData eC = {19, 'C'};
    BTreeNodeData eD = {39, 'D'};
    BTreeNodeData eE = {65, 'E'};
    BTreeNodeData eF = {53, 'F'};
    BTreeNodeData eG = {63, 'G'};
    BTreeNodeData eH = {89, 'H'};
    BTreeNodeData eI = {48, 'I'};
    BTreeNodeData eJ = {36, 'J'};
    
    pTree = createBTree();
    if (pTree != NULL)
    {
        addDataBT(pTree, eA);
        addDataBT(pTree, eB);
        addDataBT(pTree, eC);
        addDataBT(pTree, eD);
        printf("\n01-자료 추가중\n");
        displayBTree(pTree);
        
        addDataBT(pTree, eE);
        printf("\n02-자료 추가중\n");
        displayBTree(pTree);
        
        addDataBT(pTree, eF);
        addDataBT(pTree, eG);
        addDataBT(pTree, eH);
        printf("\n03-자료 추가중\n");
        displayBTree(pTree);
        
        addDataBT(pTree, eI);
        addDataBT(pTree, eJ);
        
        printf("\n자료 추가가 끝났습니다\n");
        displayBTree(pTree);
        
        removeDataBT(pTree, 9);
        printf("\n검색 키 9가 삭제되었습니다\n");
        displayBTree(pTree);
        
        removeDataBT(pTree, 89);
        printf("\n검색 키 89이 삭제되었습니다\n");
        displayBTree(pTree);
        
        removeDataBT(pTree, 39);
        printf("\n검색 키 39이 삭제되었습니다\n");
        displayBTree(pTree);
        
        removeDataBT(pTree, 63);
        removeDataBT(pTree, 53);
        printf("\n검색 키 63, 53이 삭제되었습니다\n");
        displayBTree(pTree);
        
        removeDataBT(pTree, 36);
        printf("\n검색 키 36이 삭제되었습니다\n");
        displayBTree(pTree);
        
        key = 19;
        pSearchData = searchBT(pTree, key);
        if (pSearchData != NULL) {
            printf("검색 키-[%d], 결과-[%c]\n", key, pSearchData->value);
        }
        else {
            printf("검색 키-[%d], 결과 실패\n", key);
        }
        
        deleteBTree(pTree);
    }
    return 0;
}

/*
int main2(int argc, char *argv[])
{
    BTree *pTree = NULL;
    BTreeNodeData *pSearchElement = NULL;
    int key = 0;
    
    BTreeNodeData node = {0};
    int values[] = {68, 19, 12, 9, 97, 85, 74, 63,
        45, 42, 57, 18, 14, 17, 52, 30, 22 };
    int count = sizeof(values)/sizeof(int);
    pTree = createBTree();
    if (pTree != NULL)
    {
        for(int i = 0; i < count; i++) {
            node.key = values[i];
            node.value = 'A' + i;
            
            addDataBT(pTree, node);
            
            printf("\n[%d]-[%c],자료 추가\n", node.key, node.value);
            displayBTree(pTree);
        }
        
        deleteBTree(pTree);
    }
    return 0;
}
*/
