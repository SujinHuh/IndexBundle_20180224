//IndexBundle.c
#include"IndexBundle.h"
#include"Index.h"
#include"BusinessCardBook.h"
#include<string.h>

void IndexBundle_Create(IndexBundle *indexBundle) {
	BinaryTree_Create(&indexBundle->indexes);
	indexBundle->length = 0;
}

Index* IndexBundle_TakeIn(IndexBundle *indexBundle, BusinessCard *businessCard) {
	Index index;
	Index *indexLink;
	BinaryNode *node;
	
	strcpy(index.companyName, businessCard->company.name);
	node = BinaryTree_Search(&indexBundle->indexes, &index, CompareKeys);
	if (node != NULL) {
		Index_Create(&index, 100);
		strcpy(index.companyName, businessCard->company.name);
		node = BinaryTree_Insert(&indexBundle->indexes, &index, sizeof(Index), CompareKeys);
		indexBundle->length++;
	}
	indexLink = (Index*)(node + 1);
	Index_TakeIn(indexLink, businessCard);

	return indexLink;
}

Index* IndexBundle_TakeOut(IndexBundle *indexBundle, char(*companyName), BusinessCard *businessCard) {
	Index index;
	Index *indexLink;
	BinaryNode *node;
	Long integer;

	strcpy(index.companyName, companyName);
	node = BinaryTree_Search(&indexBundle->indexes, &index, CompareKeys);
	indexLink = (Index*)(node + 1);
	integer = Index_Find(indexLink, businessCard);
	Index_TakeOut(indexLink, integer);
	if (indexLink->length == 0) {
		Index_Destroy(indexLink);
		BinaryTree_Delete(&indexBundle->indexes, &index, CompareKeys);
		indexBundle->length--;
		indexLink = NULL;
	}
	return indexLink;
}

Index* IndexBundle_Find(IndexBundle *indexBundle, char(*companyName)) {
	Index index;
	Index *indexLink = NULL;
	BinaryNode *node;

	strcpy(index.companyName, companyName);
	node = BinaryTree_Search(&indexBundle->indexes, &index, CompareKeys);
	if (node != NULL) {
		indexLink = (Index*)(node + 1);
	}
	return indexLink;
} 

void Arrange(IndexBundle *indexBundle) {
	BinaryTree_MakeBalance(&indexBundle->indexes, sizeof(Index));
}

void MakeList(IndexBundle *indexBundle, Index *(*indexes), Long *count) {
	BinaryTree_CopyToBuffer(&indexBundle->indexes, indexes, count, sizeof(Index));
}
void IndexBundle_Destroy(IndexBundle *indexBundle) {
	Destroy_Index(indexBundle->indexes.root);
	BinaryTree_Destroy(&indexBundle->indexes);
}

void Destroy_Index(BinaryNode *node) {
	if (node != NULL) {
		Destroy_Index(node->left);
		Destroy_Index(node->right);
		IndexBundle_Destroy((Index*)(node + 1));
	}
}

int CompareKeys(void *one, void *other) {
	Index *one_ = (Index*)one;
	Index *other_ = (Index*)other;

	return strcmp(one_->companyName, other_->companyName);
}