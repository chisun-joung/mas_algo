#ifndef _HASH_SEARCH_
#define _HASH_SEARCH_

#define HASH_KEY_SIZE	30

typedef enum HashBucketStatusType { EMPTY = 0, USED, DELETED  } HashBucketStatus;

typedef struct HashBucketType {
	char key[HASH_KEY_SIZE + 1];
	int value;
	HashBucketStatus status;
} HashBucket;

typedef struct HashTableType {
	int bucketSize;
	int currentCount;
	HashBucket *pBucket;
} HashTable;

// 해시 테이블의 생성.
HashTable* createHashTable(int bucketSize);

// 자료 추가.
int addData(HashTable* pHashTable, HashBucket bucket);

// 자료 제거.
int removeData(HashTable* pHashTable, char* key);

// 자료 검색.
HashBucket* search(HashTable* pHashTable, char* key);

// 해시 테이블 내용 표시.
void displayHashTable(HashTable *pHashTable);

// 해시 테이블의 현재 자료의 개수.
int getCount(HashTable *pHashTable);

// 해시 테이블의 삭제.
void deleteHashTable(HashTable *pHashTable);

// 나머지 내부에서 사용되는 함수들.
int hashFunction(char *pKey, int bucketSize);
unsigned int stringToInt(char *pKey);
int isEmptyBucket(HashBucket* pBucket);
int isEmptyOrDeletedBucket(HashBucket* pBucket);

#endif
