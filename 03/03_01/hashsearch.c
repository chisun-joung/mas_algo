#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashsearch.h"

// 해시 테이블 생성.
HashTable* createHashTable(int bucketSize) {
	HashTable *pReturn = NULL;

	if (bucketSize <= 0) {
		printf("버킷 크기는 0보다 커야합니다\n");
		return NULL;
	}

	pReturn = (HashTable *)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->currentCount = 0;
		pReturn->bucketSize = bucketSize;
		pReturn->pBucket = NULL;
	}
	else {
		printf("오류, 첫번째 메모리할당, createHashTable()\n");
		return NULL;
	}

	pReturn->pBucket = (HashBucket *)malloc(sizeof(HashBucket) * bucketSize);
	if (pReturn->pBucket != NULL) {
		memset(pReturn->pBucket, 0, sizeof(HashBucket) * bucketSize);
	}
	else {
		if (pReturn != NULL) free(pReturn);
		printf("오류, 두번째 메모리할당, createHashTable()\n");
		return NULL;
	}
	return pReturn;	
}

// 자료 추가.
int addData(HashTable* pHashTable, HashBucket bucket) {
	int ret = 0;
	HashBucket *pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;
	int inc = 1;

	if (pHashTable == NULL) {
		printf("오류,NULL-해시 테이블입니다\n");
		ret = 0;
		return ret;
	}

	bucketIndex = hashFunction(bucket.key, pHashTable->bucketSize);
	if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
		printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다, addSHT()\n");
		ret = 0;
		return ret;
	}

	tempIndex = bucketIndex;

	do {
		pBucket = &(pHashTable->pBucket[tempIndex]);

		// 1) 빈 주소 혹은 삭제된 주소인지 점검.
		if (isEmptyOrDeletedBucket(pBucket) == 1) {
			pHashTable->pBucket[tempIndex] = bucket;
			pHashTable->pBucket[tempIndex].status = USED;
			pHashTable->currentCount++;
			ret = 1;
			break;
		}
		else {	// 2) 빈 버켓을 찾지 못한 경우.
			// 2-1) 동일한 key가 이미 존재하는 경우.
			if (strcmp(pBucket->key, bucket.key) == 0) {
				printf("오류, 중복된 키-[%s], addSHT()\n",
						bucket.key);
				ret = 0;
				break;
			}
			else { // 2-2) 동일하지 않는 key인 경우, 다음 버켓으로 이동.
				tempIndex = (tempIndex + inc) % pHashTable->bucketSize;

				// 해시 테이블의 모든 버켓이 모두 찬 경우.
				if (tempIndex == bucketIndex) {
					printf("오류, 해시 테이블이 가득찼습니다\n");
					ret = 0;
					break;
				}
			}					
		}
	}
	while(tempIndex != bucketIndex);

	return ret;
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

// 빈 주소 혹은 삭제된 주소인지 점검.
int isEmptyOrDeletedBucket(HashBucket* pBucket) {
	int ret = 0;

	if (pBucket != NULL) {
		if (pBucket->status == EMPTY
			|| pBucket->status == DELETED) {
			ret = 1;
		}
	}

	return ret;
}

// 자료 검색.
HashBucket* search(HashTable* pHashTable, char* key) {
	HashBucket* pReturn = NULL;
	HashBucket *pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;

	if (pHashTable == NULL) {
		printf("오류,NULL-해시 테이블입니다\n");
		pReturn = NULL;
		return pReturn;
	}

	bucketIndex = hashFunction(key, pHashTable->bucketSize);
	if (bucketIndex < 0) {
		printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다\n");
		pReturn = NULL;
		return pReturn;
	}

	tempIndex = bucketIndex;

	do {
		pBucket = &(pHashTable->pBucket[tempIndex]);

		// 1) 빈 버켓을 찾은 경우. 검색 실패.
		if (isEmptyBucket(pBucket) == 1) {
			printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
			pReturn = NULL;
			break;
		}
		else {
			// 2-1) 동일한 key를 찾은 경우. 검색 성공.
			if (pBucket->status == USED 
					&& strcmp(pBucket->key, key) == 0) {
				pReturn = pBucket;
				break;
			}
			else { // 2-2) 동일하지 않는 key인 경우, 다음 주소로 이동.
				tempIndex = (tempIndex + 1) % pHashTable->bucketSize;
				
				// 해시 테이블의 모든 버켓을 검사한 경우.
				if (tempIndex == bucketIndex) {
					printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
					pReturn = NULL;
					break;
				}
			}					
		}
	}
	while(tempIndex != bucketIndex);

	return pReturn;
}

// 빈 주소인지 점검.
int isEmptyBucket(HashBucket* pBucket) {
	int ret = 0;

	if (pBucket != NULL) {
		if (pBucket->status == EMPTY) {
			ret = 1;
		}
	}

	return ret;
}

// 자료 제거.
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashBucket *pBucket = NULL;

	if (pHashTable != NULL) {
		pBucket = search(pHashTable, key);
		if (pBucket != NULL) {
			pBucket->status = DELETED;
			pBucket->key[0] = '\0';
			pBucket->value = 0;
			pHashTable->currentCount--;
			ret = 1;
		}
		else {
			printf("제거 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
		}
	}

	return ret;
}

// 해시 테이블 삭제.
void deleteHashTable(HashTable *pHashTable) {
	if (pHashTable != NULL) {
		free(pHashTable->pBucket);
	}
	free(pHashTable);
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
	int i = 0;
	int bucketIndex = 0;

	HashBucket *pBucket = NULL;
	if (pHashTable != NULL) {
		printf("-----------------------------------------\n");

		for(i = 0; i < pHashTable->bucketSize; i++) {
			printf("[%d],", i);

			pBucket = &(pHashTable->pBucket[i]);
			if (pBucket->key[0] != '\0') {
				bucketIndex = hashFunction(pBucket->key, pHashTable->bucketSize);

				printf("%s, (%d->%d), [%d]\n", pBucket->key, 
					bucketIndex, i,
					pBucket->value);
			}
			else {
				printf("비었습니다\n");
			}
		}

		printf("-----------------------------------------\n");
	}
	else {
		printf("NULL-해시 테이블입니다\n");
	}
}
