#include "huffman.h"

HuffmanTreeNode* makeNewHuffmanTreeNode(char data) {
    HuffmanTreeNode* pReturn = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
    if (pReturn != NULL) {
        pReturn->data = data;
        pReturn->pLeftChild = NULL;
        pReturn->pRightChild = NULL;
    }
    return pReturn;
}

HuffmanTree* makeHuffmanTree(HuffmanTreeNode *pRootNode) {
    HuffmanTree *pReturn = NULL;
    pReturn = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = pRootNode;
    }
    else {
        printf("오류, 메모리 할당(1), makeHuffmanTree()\n");
    }
    return pReturn;
}

void deleteBinTreeNode(HuffmanTreeNode* pNode) {
    if (pNode != NULL) {
        deleteBinTreeNode(pNode->pLeftChild);
        deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
    }
}

void deleteHuffmanTree(HuffmanTree* pBinTree) {
    if (pBinTree != NULL) {
        deleteBinTreeNode(pBinTree->pRootNode);
        free(pBinTree);
    }
}

void inorderTraversalAndPrintNode(HuffmanTreeNode *pNode) {
    if (pNode != NULL) {
        if (pNode->pLeftChild != NULL) {
            sprintf(pNode->pLeftChild->bitString, "%s0", pNode->bitString);
            inorderTraversalAndPrintNode(pNode->pLeftChild);
        }
        
        if (pNode->pLeftChild == NULL
            && pNode->pRightChild == NULL) {
            printf("%c : %s \n", pNode->data, pNode->bitString);
        }
        
        if (pNode->pRightChild != NULL) {
            sprintf(pNode->pRightChild->bitString, "%s1", pNode->bitString);
            inorderTraversalAndPrintNode(pNode->pRightChild);
        }
    }
}

void printHuffmanTree(HuffmanTree *pBinTree) {
    if (pBinTree != NULL) {
        pBinTree->pRootNode->bitString[0] = 0;
        inorderTraversalAndPrintNode(pBinTree->pRootNode);
        printf("\n");
    }
}

void inorderTraversalAndupateBitstring(HuffmanTreeNode *pNode, HuffmanCode *pHuffmanCodeTable) {
    if (pNode != NULL) {
        if (pNode->pLeftChild != NULL) {
            sprintf(pNode->pLeftChild->bitString, "%s0", pNode->bitString);
            inorderTraversalAndupateBitstring(pNode->pLeftChild, pHuffmanCodeTable);
        }
        
        if (pNode->pLeftChild == NULL
            && pNode->pRightChild == NULL) {
            int index = (int)pNode->data;
            strcpy(pHuffmanCodeTable[index].bitString, pNode->bitString);
        }
        
        if (pNode->pRightChild != NULL) {
            sprintf(pNode->pRightChild->bitString, "%s1", pNode->bitString);
            inorderTraversalAndupateBitstring(pNode->pRightChild, pHuffmanCodeTable);
        }
    }
}

void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable) {
    if (pHuffmanTree != NULL) {
        pHuffmanTree->pRootNode->bitString[0] = 0;
        inorderTraversalAndupateBitstring(pHuffmanTree->pRootNode, pHuffmanCodeTable);
    }
}

void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount)
{
    long count = 0, i = 0;
    
    if (pSourceString == NULL || pSourceCode == NULL)
        return;
    
    memset(pSourceCode, 0, sizeof(HuffmanCode)*codeCount);
    for(i = 0; i < codeCount; i++) {
        pSourceCode[i].data = (char)i;
    }
    
    count = strlen(pSourceString);
    for(i = 0; i < count; i++) {
        int asc = pSourceString[i];
        pSourceCode[asc].frequency++;
    }
}

HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes) {
    HuffmanTree *pHuffmanTree = NULL;
    ArrayMinHeap* pHeap = NULL;
    HeapNode *pLastHeapNode = NULL;
    int i = 0, unique_char_num = 0;
    
    pHeap = createArrayHeap(COUNT_ASC);
    if (pHeap == NULL) {
        return pHuffmanTree;
    }
    
    for(i = 0; i < COUNT_ASC; i++) {
        if (pCodes[i].frequency > 0) {
            HeapNode heapNode = {0};
            heapNode.frequency = pCodes[i].frequency;
            heapNode.pData = makeNewHuffmanTreeNode(pCodes[i].data);
            
            insertMinHeapAH(pHeap, heapNode);
        }
    }
    
    unique_char_num = pHeap->currentCount;
    for(i=0; i < unique_char_num - 1; i++) {
        HeapNode *pLeft = deleteMinHeapAH(pHeap);
        HeapNode *pRight = deleteMinHeapAH(pHeap);
        if (pRight != NULL && pLeft != NULL) {
            HeapNode heapNode = {0};
            HuffmanTreeNode *pHuffmanNode = NULL;
            
            pHuffmanNode = makeNewHuffmanTreeNode('?');
            pHuffmanNode->pLeftChild = pLeft->pData;
            pHuffmanNode->pRightChild = pRight->pData;
            
            heapNode.frequency = pRight->frequency + pLeft->frequency;
            heapNode.pData = pHuffmanNode;
            
            insertMinHeapAH(pHeap, heapNode);
            
            free(pRight);
            free(pLeft);
        }
    }
    
    pLastHeapNode = deleteMinHeapAH(pHeap);
    if (pLastHeapNode != NULL) {
        pHuffmanTree = makeHuffmanTree(pLastHeapNode->pData);
    }
    
    deleteArrayHeap(pHeap);
    
    return pHuffmanTree;
}

char* getEncodedString(char *pSourceString, HuffmanCode* pHuffmanCodeTable) {
    char *pReturn = NULL;
    long count = 0, i = 0;
    
    if (pSourceString == NULL || pHuffmanCodeTable == NULL)
        return pReturn;
    
    count = strlen(pSourceString);
    pReturn = (char*)malloc(sizeof(char) * count * (MAX_BIT_SIZE + 1));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(char) * count * (MAX_BIT_SIZE + 1));
        for(i = 0; i < count; i++) {
            int index = (int)pSourceString[i];
            strcat(pReturn, pHuffmanCodeTable[index].bitString);
        }
    }
    
    return pReturn;
}

char* getDecodedString(char *pSourceString, HuffmanTree *pHuffmanTree) {
    char *pReturn = NULL;
    HuffmanTreeNode *pNode = NULL;
    long count = 0, i = 0;
    
    if (pSourceString == NULL || pHuffmanTree == NULL)
        return pReturn;
    
    count = strlen(pSourceString);
    pReturn = (char*)malloc(sizeof(char) * count);
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(char) * count);
        
        pNode = pHuffmanTree->pRootNode;
        for(i = 0; i < count; i++) {
            char bit = (char)pSourceString[i];
            //strcat(pReturn, pHuffmanCodeTable[index].bitString);
            
            if ('0' == bit) {
                pNode = pNode->pLeftChild;
            }
            else {
                pNode = pNode->pRightChild;
            }
            if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
                sprintf(pReturn, "%s%c", pReturn, pNode->data);
                pNode = pHuffmanTree->pRootNode;
            }
        }
    }
    
    return pReturn;
}
