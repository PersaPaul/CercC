#pragma once

typedef struct _CC_LIST_ENTRY {
	int Value;
	int FirstNode;
	struct _CC_LIST_ENTRY *Next;
} CC_LIST_ENTRY;

int LstCreate(CC_LIST_ENTRY **List); 
int LstDestroy(CC_LIST_ENTRY **List); 
int LstInsertValue(CC_LIST_ENTRY *List, int Value); 
int LstRemoveNode(CC_LIST_ENTRY *List, CC_LIST_ENTRY *Node); 
int LstGetNodeValue(CC_LIST_ENTRY *Node, int *Value); 
int LstGetNthNode(CC_LIST_ENTRY *List, int Index, CC_LIST_ENTRY **Node); 
int LstGetNodeCount(CC_LIST_ENTRY *List);
int LstClear(CC_LIST_ENTRY *List); 
int LstSortByValues(CC_LIST_ENTRY *List); 
int LstMergeSortedLists(CC_LIST_ENTRY *Destination, CC_LIST_ENTRY *Source); 