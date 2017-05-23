#include <stdio.h>
#include <stdlib.h>
#include "hashsearch.h"

int main(int argc, char *argv[])
{
    HashTable *pHashTable = NULL;
    HashBucket bucket1 = {"january", 1};
    HashBucket bucket2 = {"february", 2};
    HashBucket bucket3 = {"march", 3};
    HashBucket bucket4 = {"april", 4};
    HashBucket bucket5 = {"may", 5};
    HashBucket bucket6 = {"june", 6};
    HashBucket bucket7 = {"july", 7};
    HashBucket bucket8 = {"august", 8};
    HashBucket bucket9 = {"september", 9};
    HashBucket bucket10 = {"october", 10};
    HashBucket bucket11 = {"november", 11};
    HashBucket bucket12 = {"december", 12};
    HashBucket *pBucket = NULL;
    HashBucket *pBucket2 = NULL;
    
    // 해시 테이블 생성
    pHashTable = createHashTable(13);
    if (pHashTable != NULL) {
        addData(pHashTable, bucket1);
        addData(pHashTable, bucket2);
        addData(pHashTable, bucket3);
        addData(pHashTable, bucket4);
        addData(pHashTable, bucket5);
        addData(pHashTable, bucket6);
        addData(pHashTable, bucket7);
        addData(pHashTable, bucket8);
        addData(pHashTable, bucket9);
        addData(pHashTable, bucket10);
        addData(pHashTable, bucket11);
        addData(pHashTable, bucket12);
        
        printf("해시 테이블 내용:\n");
        displayHashTable(pHashTable);
        
        pBucket = search(pHashTable, "april");
        if (pBucket != NULL) {
            printf("검색키-%s, 검색 결과-%d\n", pBucket->key, pBucket->value);
            
            removeData(pHashTable, "april");
            printf("검색키[%s]로 자료 제거\n", "april");
            
            printf("해시 테이블 내용:\n");
            displayHashTable(pHashTable);
            
            pBucket2 = search(pHashTable, "april");
            if (pBucket2 != NULL) {
                printf("검색키-%s, 검색 결과-%d\n", pBucket2->key, pBucket2->value);
            }
            
            pBucket2 = search(pHashTable, "june");
            if (pBucket2 != NULL) {
                printf("검색키-%s, 검색 결과-%d\n", pBucket2->key, pBucket2->value);
            }
        }
        else {
            printf("발견하지 못했습니다\n");
        }
        
        deleteHashTable(pHashTable);
    }
    
    return 0;
}
