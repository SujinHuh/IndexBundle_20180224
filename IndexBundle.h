//IndexBundle.h
#ifndef _INDEXBUNDLE_H
#define _INDEXBUNDLE_H
#include"BinaryTree.h"
typedef signed long int Long;

typedef struct _index Index;
typedef struct _businessCard BusinessCard;
typedef struct _indexBundle {
	BinaryTree indexes;
	Long length;
}IndexBundle;

void IndexBundle_Create(IndexBundle *indexBundle);
Index* IndexBundle_TakeIn(IndexBundle *indexBundle, BusinessCard *businessCard);
Index* IndexBundle_TakeOut(IndexBundle *indexBundle, char(*companyName), BusinessCard *businessCard);
Index* IndexBundle_Find(IndexBundle *indexBundle, char(*companyName));
void Arrange(IndexBundle *indexBundle);
void MakeList(IndexBundle *indexBundle, Index *(*indexes), Long *count);
void IndexBundle_Destroy(IndexBundle *indexBundle);
void Destroy_Index(BinaryNode *node);
int CompareKeys(void *one, void *other);

#endif //_INDEXBUNDLE_H