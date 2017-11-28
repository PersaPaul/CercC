#include <stdlib.h>
#include "cctree.h"
#include "errors.h"


int TreeCreate(CC_TREE **Tree)
{
	if (NULL == Tree)
	{
		return INVALIDPARAMETER1;
	}
	*Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
	if (*Tree == NULL)
	{
		free(*Tree);
		return INVALIDMEMORY;
	}
	(*Tree)->Left = NULL;
	(*Tree)->Right = NULL;
	(*Tree)->FirstNode = 1;
	(*Tree)->Height = 1;
	return 0;
}
int TreeDestroy(CC_TREE **Tree)
{
	if (NULL == Tree)
	{
		return INVALIDPARAMETER1;
	}
	free(Tree); // cred ca trebuie la toate
	return 0;
}
int TreeInsert(CC_TREE *Tree, int Value)
{
	if (NULL == Tree)
	{
		Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
		Tree->Left = NULL;
		Tree->Right = NULL;
		Tree->FirstNode = 0;
		Tree->Height = 1;
		Tree->Value = Value;
	}
	if (Tree->FirstNode == 1)
	{
		Tree->FirstNode = 0;
		Tree->Value = Value;
	}
	return 0;
}
int TreeRemove(CC_TREE *Tree, int Value)
{

	return 0;
}
int TreeContains(CC_TREE *Tree, int Value)
{

	return 0;
}
int TreeGetCount(CC_TREE *Tree)
{

	return 0;
}
int TreeGetHeight(CC_TREE *Tree)
{

	return 0;
}
int TreeClear(CC_TREE *Tree)
{

	return 0;
}
int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{

	return 0;
}
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{

	return 0;
}
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{

	return 0;
}