//Index.c
#include"Index.h"
#include<string.h>

void Index_Create(Index *index, Long capacity) {
	Create(&index->index, capacity, sizeof(BusinessCard*));
	index->capacity = capacity;
	index->length = 0;
	srtcpy(index->companyName, "");
}

Long Index_TakeIn(Index *index, BusinessCard *businessCard) {
	Long integer;

	integer = index->length;
	if (index->length < index->capacity) {
		integer = Store(&index->index, integer, &businessCard, sizeof(BusinessCard*));
	}
	else {
		integer = AppendFromRear(&index->index, &businessCard, sizeof(BusinessCard*));
		index->capacity++;
	}
	index->length++;

	return integer;
}

Long Index_TakeOut(Index *index, Long integer) {
	integer = Delete(&index->index, integer, sizeof(BusinessCard*));
	index->capacity--;
	index->capacity--;

	return integer;
}

Long Index_Find(Index *index, BusinessCard *businessCard) {
	Long integer;

	integer = LinerSearchUnique(&index->index, businessCard, sizeof(BusinessCard*), ComparePointers);

	return integer;
}

BusinessCard* Index_GetAt(Index *index, Long integer) {
	BusinessCard *businessCard;

	GetAt(&index->index, integer, &businessCard, sizeof(BusinessCard*));

	return businessCard;
}

void Index_Destroy(Index *index) {

	Destroy(&index->index);
}

int ComparePointers(void *one, void *other) {
	int ret = 1;
	BusinessCard *one_ = (BusinessCard**)one;

	if (one_ == other) {
		ret = 0;
	}
	return ret;
}