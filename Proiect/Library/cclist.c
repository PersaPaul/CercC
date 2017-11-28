#include <stdlib.h>

#include "cclist.h"
#include "errors.h"

int LstCreate(CC_LIST_ENTRY **List)
{
	if (List == NULL)
		return INVALIDPARAMETER1;
	(*List) = (CC_LIST_ENTRY*)malloc(sizeof(CC_LIST_ENTRY));
	if ((*List) == NULL)
	{
		free(*List);
		return INVALIDMEMORY;
	}
	(*List)->FirstNode = 1;
	(*List)->Next = NULL;
	
	return 0;
}

int LstDestroy(CC_LIST_ENTRY **List)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
		return 0;
	}

	CC_LIST_ENTRY *Previous;
	while ((*List)->Next!= NULL)
	{
		Previous = (*List);
		(*List) = (*List)->Next;
		free(Previous);
	}
	free(*List);
	*List = NULL;
	return 0;
}

int LstInsertValue(CC_LIST_ENTRY *List, int Value) //todo first node
{
	if (List == NULL)
		return INVALIDPARAMETER1;
	
	if(List->FirstNode)
	{
		List->Value = Value;
		List->FirstNode = 0;
		return 0;
	}
	
	CC_LIST_ENTRY* New;
	New = (CC_LIST_ENTRY*)malloc(sizeof(CC_LIST_ENTRY));
	if (New == NULL)
	{
		free(New);
		return INVALIDMEMORY;
	}
	while (List->Next != NULL)
		List = List->Next;
	List->Next = New;
	New->Value = Value;
	New->Next = NULL;
	return 0;
}

int LstRemoveNode(CC_LIST_ENTRY *List, CC_LIST_ENTRY *Node)
{
	if (List == NULL)
		return INVALIDPARAMETER1;
	if (Node == NULL || Node->FirstNode==1)
		return INVALIDPARAMETER2;
	if (List == Node)
	{
		if (List->Next == NULL)
			return ERROREMPTYLIST;
		List->Value = List->Next->Value;
		Node = Node->Next;
		List->Next = List->Next->Next;
		return 0;
	}
	while (List->Next != Node && List != NULL)
	{
		List = List->Next;
	}
	if (List == NULL)
		return INVALIDPARAMETER2;
	List->Next = Node->Next;
	free(Node);
	return 0;
}

int LstGetNodeValue(CC_LIST_ENTRY *Node, int *Value) 
{
	if (Node == NULL || Node->FirstNode==1)
		return INVALIDPARAMETER1;
	(*Value) = (Node->Value);
	return 0;
}

int LstGetNthNode(CC_LIST_ENTRY *List,int Index, CC_LIST_ENTRY **Node)
{
	if (List == NULL || List->FirstNode==1)
		return INVALIDPARAMETER1;
	int i = 0;
	while (i < Index && List != NULL)
	{
		i++;
		List = List->Next;
	}
	if (List == NULL)
	{
		return INVALIDPARAMETER2;
	}
	else
		*Node = List;
	return 0;
}

int LstGetNodeCount(CC_LIST_ENTRY *List)
{
	int Count = 0;
	if (List == NULL || List->FirstNode==1)
		return INVALIDPARAMETER1;
	while (List != NULL)
	{
		Count++;
		List = List->Next;
	}
	return Count;
}

int LstClear(CC_LIST_ENTRY *List)
{
	if (List == NULL || List->FirstNode==1)
	{
		return INVALIDPARAMETER1;
	}
	List->FirstNode = 1;
	CC_LIST_ENTRY *Previous,*First;
	First = List;
	List = List->Next;
	Previous = List;
	while (List != NULL)
	{
		Previous = List;
		List = List->Next;
		free(Previous);
	}
	First->Next = NULL;
	return 0;
}

int LstSplit(CC_LIST_ENTRY*, CC_LIST_ENTRY*);

int LstSortByValues(CC_LIST_ENTRY *List)
{
	if (List == NULL || List->Next == NULL)
	{
		return 0;
	}
	
	CC_LIST_ENTRY *FirstList = NULL, *LastList = NULL;
	LstSplit(List, &FirstList, &LastList);
	LstSortByValues(FirstList);
	LstSortByValues(LastList);
	LstMergeSortedLists(FirstList, LastList);
	List = FirstList;
	return 0;
}

int LstSplit(CC_LIST_ENTRY *List, CC_LIST_ENTRY **FirstList, CC_LIST_ENTRY **LastList)
{
	if (List->Next == NULL)
	{
		(*FirstList) = List;
		(*LastList) = NULL;
		return 0;
	}
	
	CC_LIST_ENTRY* End;
	CC_LIST_ENTRY* Mid;
	Mid = List;
	End = List->Next;
	while (End != NULL)
	{
		End = End->Next;
		if (End != NULL)
		{
			Mid = Mid->Next;
			End = End->Next;
		}
	}
	(*FirstList) = List;
	(*LastList) = Mid->Next;
	Mid->Next = NULL;
	return 0;
}

int LstMergeSortedLists(CC_LIST_ENTRY *Destination, CC_LIST_ENTRY *Source)
{
	CC_LIST_ENTRY *Current = NULL;
	int aux;
	if (Destination == NULL)
		return INVALIDPARAMETER1;
	if (Source == NULL)
		return INVALIDPARAMETER2;

	while (Source != NULL  && Destination->Value > Source->Value)
	{
		Current = Source;
		Source = Source->Next;
		Current->Next = Destination->Next;
		Destination->Next = Current;
		aux = Current->Value;
		Current->Value = Destination->Value;
		Destination->Value = aux;
	}

	while (Destination->Next != NULL && Source != NULL)
	{
		if (Destination->Next->Value > Source->Value)
		{
			Current = Source;
			Source = Source->Next;
			Current->Next = Destination->Next;
			Destination->Next = Current;
		}
		else
		{
			Destination = Destination->Next;
		}
	}
	if (Source != NULL)
	{
		Destination->Next = Source;
	}

	return 0;
}