//Index.h
#ifndef _INDEX_H
#define _INDEX_H
#include"Array.h"

typedef signed long int Long;

typedef struct _buinessCard BusinessCard;
typedef struct _index {
	Array index;
	Long capacity;
	Long length;
	char companyName[64];
}Index;

void Index_Create(Index *index, Long capacity);
Long Index_TakeIn(Index *index, BusinessCard *businessCard);
Long Index_TakeOut(Index *index, Long integer);
Long Index_Find(Index *index, BusinessCard *businessCard);
BusinessCard* Index_GetAt(Index *index, Long integer);
void Index_Destroy(Index *index);
int ComparePointers(void *one, void *other);

#endif //_INDEX_H