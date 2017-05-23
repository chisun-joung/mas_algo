#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

int main()
{
    HuffmanTree* pHuffmanTree = NULL;
    HuffmanCode *pHuffmanCodeTable = NULL;
    
    char sourceString[] = "ABCDABCABA";
    char *pEncodedString = NULL;
    char *pDecodedString = NULL;
    
    pHuffmanCodeTable = (HuffmanCode*)malloc(sizeof(HuffmanCode) * COUNT_ASC);
    checkFrequency(sourceString, pHuffmanCodeTable, COUNT_ASC);
    
    pHuffmanTree = buildHuffmanTree(pHuffmanCodeTable);
    applyBitstring(pHuffmanTree, pHuffmanCodeTable);
    printHuffmanTree( pHuffmanTree );
    
    pEncodedString = getEncodedString(sourceString, pHuffmanCodeTable);
    pDecodedString = getDecodedString(pEncodedString, pHuffmanTree);
    
    printf("원본 문자열: %s\n", sourceString);
    printf("허프만 인코딩 문자열: %s\n", pEncodedString);
    printf("허프만 디코딩 문자열: %s\n", pDecodedString);
    
    if (pDecodedString != NULL) free(pDecodedString);
    if (pEncodedString != NULL) free(pEncodedString);
    deleteHuffmanTree(pHuffmanTree);
    if (pHuffmanCodeTable != NULL) free(pHuffmanCodeTable);
    
    return 0;
}
