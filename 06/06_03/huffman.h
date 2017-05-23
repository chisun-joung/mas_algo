#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrayheap.h"

#define MAX_BIT_SIZE    8
#define COUNT_ASC       128

typedef struct HuffmanTreeNodeType
{
    char data;
    char bitString[MAX_BIT_SIZE + 1];
    
    struct HuffmanTreeNodeType* pLeftChild;
    struct HuffmanTreeNodeType* pRightChild;
} HuffmanTreeNode;

typedef struct HuffmanTreeType
{
    struct HuffmanTreeNodeType* pRootNode;
} HuffmanTree;

typedef struct HuffmanCodeType
{
    char    data;
    int     frequency;
    char    bitString[MAX_BIT_SIZE + 1];
} HuffmanCode;

void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount);
HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes);
void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable);
void printHuffmanTree(HuffmanTree *pBinTree);
void deleteHuffmanTree();

char* getEncodedString(char *pSourceString, HuffmanCode* pHuffmanCodeTable);
char* getDecodedString(char *pBitString, HuffmanTree *pHuffmanTree);

#endif

