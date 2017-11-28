#pragma once

typedef struct _CC_TREE {
	int Value;
	struct _CC_TREE *Left;
	struct _CC_TREE *Right;
	int Height;
	int FirstNode;
} CC_TREE;

int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree); //todo free la toate
int TreeInsert(CC_TREE *Tree, int Value);
int TreeRemove(CC_TREE *Tree, int Value);
int TreeContains(CC_TREE *Tree, int Value);
int TreeGetCount(CC_TREE *Tree);
int TreeGetHeight(CC_TREE *Tree);
int TreeClear(CC_TREE *Tree);
int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);

