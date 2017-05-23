#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashsearch_chain.h"

// 해시 테이블 생성.
HashTable* createHashTable(int bucketSize) {
	HashTable *pReturn = NULL;
    int i = 0;

	if (bucketSize <= 0) {
		printf("버킷 크기는 0보다 커야합니다\n");
		return NULL;
	}

	pReturn = (HashTable *)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->bucketSize = bucketSize;
		pReturn->ppBucket = NULL;
	}
	else {
		printf("오류, 첫번째 메모리할당, createHashTable()\n");
		return NULL;
	}

    pReturn->ppBucket = (LinkedList **)malloc(sizeof(LinkedList*) * bucketSize);
    if (pReturn->ppBucket != NULL) {
        memset(pReturn->ppBucket, 0, sizeof(LinkedList*) * bucketSize);
        
        for(i = 0; i < bucketSize; i++) {
            pReturn->ppBucket[i] = createLinkedList();
        }
    }
    else {
        printf("오류, 두번째 malloc(), createHashTable()\n");
        return NULL;
    }
	return pReturn;
}

// 자료 추가.
int addData(HashTable* pHashTable, HashSlot slot) {
    int ret = 0;
    LinkedList* pBucket = NULL;
    
    if (pHashTable != NULL) {
        pBucket = searchBucket(pHashTable, slot.key);
        if (pBucket != NULL) {
            addLinkedListDataLast(pBucket, slot);
            pHashTable->currentCount++;
        }
        else {
            printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다\n");
        }
    }
    
    return ret;
}

LinkedList* searchBucket(HashTable* pHashTable, char* key) {
    LinkedList* pReturn = NULL;
    int bucketIndex = 0;
    
    if (pHashTable != NULL) {
        bucketIndex = hashFunction(key, pHashTable->bucketSize);
        if (bucketIndex >= 0) {
            pReturn = pHashTable->ppBucket[bucketIndex];
        }
        else {
            printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다,\n");
        }
    }
    
    return pReturn;
}

int hashFunction(char *pKey, int bucketSize) {
    int ret = -1;
    unsigned int temp_key = 0;
    
    if (pKey == NULL) {
        return ret;
    }
    
    temp_key = stringToInt(pKey);
    if (bucketSize > 0) {
        ret = temp_key % bucketSize;
    }
    
    return ret;
}

// 문자열을 숫자로 변환.
unsigned int stringToInt(char *pKey) {
    unsigned int ret = 0;
    while(*pKey != '\0') {
        ret = (ret * 31) + (*pKey);
        pKey++;
    }
    
    return ret;
}

// 리스트 제일 마지막에 추가.
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data) {
    int ret = 0;
    if (pBucket != NULL) {
        int position = pBucket->currentCount;
        ret = addLinkedListData(pBucket, position, data);
    }
    return ret;
}

// 자료 검색.
HashSlot* search(HashTable* pHashTable, char* key) {
	HashSlot* pReturn = NULL;
    LinkedList* pList = NULL;
    int position = 0;
    
    pList = searchBucket(pHashTable, key);
    if (pList != NULL) {
        pReturn = searchSlot(pList, key, &position);
    }

	return pReturn;
}

HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition) {
    HashSlot* pReturn = NULL;
    LinkedListNode* pSlot = NULL;
    int index = 0;
    
    if (pList != NULL && pPosition != NULL) {
        pSlot = pList->headerNode.pLink;
        
        while(pSlot != NULL) {
            if (strcmp(pSlot->data.key, key) == 0) {
                pReturn = &(pSlot->data);
                *pPosition = index;
                break;
            }
            pSlot = pSlot->pLink;
            index++;
        }
        if (pReturn == NULL) {
            printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
        }
    }
    
    return pReturn;
}

// 자료 제거.
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashSlot *pSlot = NULL;
    LinkedList* pList = NULL;
    int position = 0;
    
    pList = searchBucket(pHashTable, key);
    if (pList != NULL) {
        pSlot = searchSlot(pList, key, &position);
        if (pSlot != NULL) {
            removeLinkedListData(pList, position);
            pHashTable->currentCount--;
            ret = 1;
        }
    }

	return ret;
}

// 해시 테이블 삭제.
void deleteHashTable(HashTable *pHashTable) {
    int i = 0;
    if (pHashTable != NULL) {
        if (pHashTable->ppBucket != NULL) {
            for(i = 0; i < pHashTable->bucketSize; i++) {
                deleteLinkedList( pHashTable->ppBucket[i] );
            }
            free(pHashTable->ppBucket);
        }
        free(pHashTable);
    }
}

// 해시 테이블의 현재 자료 개수.
int getCount(HashTable *pHashTable) {
	int ret = 0;

	if (pHashTable != NULL) {
		ret = pHashTable->currentCount;
	}

	return ret;
}

// 해시 테이블 내용 출력.
void displayHashTable(HashTable *pHashTable) {
    int i = 0, j = 0;
    int slotSize = 0;
    LinkedList* pList = NULL;
    LinkedListNode* pNode = NULL;
    
    if (pHashTable != NULL) {
        for(i = 0; i < pHashTable->bucketSize; i++) {
            printf("[%d]", i);
            
            pList = pHashTable->ppBucket[i];
            slotSize = getLinkedListLength( pList );
            if (slotSize == 0) {
                printf(",Empty \n");
            }
            else {
                pNode = pList->headerNode.pLink;
                for(j = 0; j < slotSize; j++) {
                    printf(",(%s, %d) ", pNode->data.key, pNode->data.value);
                    pNode = pNode->pLink;
                }
                printf("\n");
            }
        }
    }
}
