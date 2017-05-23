#ifndef _HASH_CHAIN_
#define _HASH_CHAIN_

#include "hashdef.h"
#include "linkedlist.h"

typedef struct HashTableType {
	int bucketSize;
	int currentCount;
	struct LinkedListType **ppBucket;
} HashTable;

// 해시 테이블 생성.
HashTable* createHashTable(int bucketSize);

// 자료 추가.
int addData(HashTable* pHashTable, HashSlot slot);

// 자료 제거.
int removeData(HashTable* pHashTable, char* key);

// 자료 검색.
HashSlot* search(HashTable* pHashTable, char* key);

// 해시 테이블 내용 표시.
void displayHashTable(HashTable *pHashTable);

// 해시 테이블의 현재 자료 개수.
int getCount(HashTable *pHashTable);

// 해시 테이블 삭제.
void deleteHashTable(HashTable *pHashTable);

// 그 외 내부적으로 사용되는 함수들.
LinkedList* searchBucket(HashTable* pHashTable, char* key);
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data);
int hashFunction(char *pKey, int bucketSize);
unsigned int stringToInt(char *pKey);
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition);

#endif
