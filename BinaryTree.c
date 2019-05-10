//BinaryTree.c
#include "BinaryTree.h"
#include <stdlib.h>
#include <memory.h>

void BinaryTree_Create(BinaryTree *binaryTree) {
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode *index;
	BinaryNode *parent = NULL;
	BinaryNode *node;

	index = binaryTree->root;
	while (index != NULL) {
		parent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(node + 1, key, size);
	node->left = NULL;
	node->right = NULL;
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		if (compare(binaryTree->root + 1, key) > 0) {
			binaryTree->balance--;
		}
		else {
			binaryTree->balance++;
		}
	}
	else {
		binaryTree->root = node;
	}
	binaryTree->length++;

	return node;
}

BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)) {
	BinaryNode* index;
	BinaryNode* parent = NULL;
	BinaryNode* temp = NULL;
	BinaryNode* tempParent = NULL;
	BinaryNode* tempChild = NULL;
	BinaryNode* rootIndex;

	index = binaryTree->root;
	rootIndex = binaryTree->root;
	while (compare(index + 1, key) != 0) {
		parent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	if (index->right != NULL) {
		temp = index;
		tempChild = temp->right;
		while (tempChild != NULL) {
			tempParent = temp;
			temp = tempChild;
			tempChild = tempChild->left;
		}
		if (temp->right != NULL) {
			if (index != tempParent) {
				tempParent->left = temp->right;
			}
			else {
				tempParent->right = temp->right;
			}
		}
		else {
			if (index != tempParent) {
				tempParent->left = NULL;
			}
			else {
				tempParent->right = NULL;
			}
		}
	}
	else if (index->left != NULL) {
		temp = index;
		tempChild = temp->left;
		while (tempChild != NULL) {
			tempParent = temp;
			temp = tempChild;
			tempChild = tempChild->right;
		}
		if (temp->left != NULL) {
			if (index != tempParent) {
				tempParent->right = temp->left;
			}
			else {
				tempParent->left = temp->left;
			}
		}
		else {
			if (index != tempParent) {
				tempParent->right = NULL;
			}
			else {
				tempParent->left = NULL;
			}
		}
	}
	if (temp != NULL) {
		temp->left = index->left;
		temp->right = index->right;
		if (parent != NULL) {
			if (compare(parent + 1, key) > 0) {
				parent->left = temp;
			}
			else {
				parent->right = temp;
			}
		}
		else {
			binaryTree->root = temp;
		}
	}
	else if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}
	else {
		binaryTree->root = NULL;
	}
	if (parent != NULL) {
		if (compare(rootIndex + 1, key) > 0) {
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	else if (temp != NULL) {
		if (compare(rootIndex + 1, key) > 0) {
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	binaryTree->length--;

	return index;
}

BinaryNode* BinaryTree_Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)) {
	BinaryNode *index;

	index = binaryTree->root;
	while (index != NULL && (compare(index + 1, key) != 0)) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

void BinaryTree_MakeBalance(BinaryTree *binaryTree, size_t size) {
	void(*buffer);
	Long count;

	BinaryTree_CopyToBuffer(binaryTree, &buffer, &count, size);
	BinaryTree_DeleteAllItems(binaryTree);
	BinaryTree_MakeTree(binaryTree, buffer, count, size);
	if (buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}
}

void BinaryTree_CopyToBuffer(BinaryTree *binaryTree, void *(*buffer), Long *count, size_t size) {
	Long i = 0;
	*count = 0;

	*buffer = (void(*))calloc(binaryTree->length, size);
	BinaryTree_Node_CopyToBuffer(binaryTree->root, *buffer, count, &i, size);
}

void BinaryTree_Node_CopyToBuffer(BinaryNode* node, void(*buffer), Long *count, Long *i, size_t size) {
	if (node != NULL) {
		BinaryTree_Node_CopyToBuffer(node->left, buffer, count, i, size);
		memcpy(((char*)buffer) + ((*i)*size), node + 1, size);
		(*i)++;
		(*count)++;
		BinaryTree_Node_CopyToBuffer(node->right, buffer, count, i, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree) {
	BinaryTree_Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void BinaryTree_Node_DeleteAllItems(BinaryNode *node) {
	if (node != NULL) {
		BinaryTree_Node_DeleteAllItems(node->left);
		BinaryTree_Node_DeleteAllItems(node->right);
		free(node);
	}
}

void BinaryTree_MakeTree(BinaryTree *binaryTree, void(*buffer), Long count, size_t size) {
	Long high;
	Long low = 0;

	high = count - 1;
	binaryTree->root = BinaryTree_Node_MakeTree(buffer, low, high, size);
	binaryTree->length = count;
	binaryTree->balance = (count + 1) % 2;
}

BinaryNode* BinaryTree_Node_MakeTree(void(*buffer), Long low, Long high, size_t size) {
	BinaryNode* node = NULL;
	Long middle;

	if (high >= low) {
		middle = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		memcpy(node + 1, ((char*)buffer) + ((middle)*size), size);
		node->left = BinaryTree_Node_MakeTree(buffer, low, middle - 1, size);
		node->right = BinaryTree_Node_MakeTree(buffer, middle + 1, high, size);
	}
	return node;
}

void BinaryTree_Destroy(BinaryTree *binaryTree) {
	BinaryTree_Node_Destroy(binaryTree->root);
}

void BinaryTree_Node_Destroy(BinaryNode *node) {
	if (node != NULL) {
		BinaryTree_Node_Destroy(node->left);
		BinaryTree_Node_Destroy(node->right);
		free(node);
	}
}

void BinaryTree_GetKey(BinaryTree *binaryTree, BinaryNode *index, void *object, size_t size) {
	memcpy(object, index + 1, size);
}