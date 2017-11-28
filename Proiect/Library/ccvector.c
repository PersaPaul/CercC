#include<stdlib.h>
#include<stdio.h>
#include "ccvector.h"
#include "errors.h"

int VecCreate(CC_VECTOR **Vector)
{
	if (Vector == NULL)
	{
		return INVALIDPARAMETER1;
	}
	(*Vector) = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
	(*Vector)->Used = 0;
	(*Vector)->Size = 10;
	(*Vector)->Array = (int*)malloc((*Vector)->Size * sizeof(int));
	if ((*Vector)->Array == NULL)
	{
		return INVALIDMEMORY;
	}
	
	(*Vector)->Start = (*Vector)->Size / 2;
	(*Vector)->End = (*Vector)->Size / 2;
	return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
	if (Vector == NULL)
	{
		return INVALIDPARAMETER1;
	}
	free(*Vector);
	return 0;
}

int VecReallocLeft(CC_VECTOR*);
int VecReallocRight(CC_VECTOR*);

int VecInsertTail(CC_VECTOR *List, int Value)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}
	List->Start--;
	List->Used++;
	List->Array[List->Start] = Value;
	int Success = 0;
	if (List->Start == 0) 
	{
		Success = VecReallocLeft(List);
		return Success;
	}
	return 0;
}

int VecInsertHead(CC_VECTOR *List, int Value)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}
	List->Used++;
	List->Array[List->End] = Value;
	List->End++;
	int Success = 0;
	if (List->End == List->Size)
	{
		Success = VecReallocRight(List);
		return Success;
	}
	return 0;
}

int VecGetValueByIndex(CC_VECTOR *List, int Index, int *Value)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}
	if (Value == NULL) 
	{
		return INVALIDPARAMETER3;
	}
	(*Value) = List->Array[(List->Start)+Index];
	return 0;
}

int VecReallocLeft(CC_VECTOR *List)
{
	int Newmem = List->Used*2;
	List->Array = (int*)realloc(List->Array, (List->Size + Newmem) * sizeof(int));

	if (List == NULL)
	{
		free(List);
		return INVALIDMEMORY;
	}

	for (int i = 0; i < List->Used; i++)
	{
		List->Array[i + Newmem] = List->Array[i];
	}

	List->Size += Newmem;
	List->Start += Newmem;
	List->End += Newmem;
	return 0;
}

int VecReallocRight(CC_VECTOR *List)
{
	int Newmem = List->Used * 2;
	List->Array = (int*)realloc(List->Array, (List->Size + Newmem) * sizeof(int));

	if (List == NULL)
	{
		free(List);
		return INVALIDMEMORY;
	}

	List->Size += Newmem;
	
	return 0;
}

int VecInsertAfterIndex(CC_VECTOR *List, int Index, int Value)
{
	if (List == NULL)
		return INVALIDPARAMETER1;
	int Success=0;

	if (Index == List->Size)
	{
		Success = VecReallocLeft(List);
	}

	if (Success)
	{
		return Success;
	}

	for (int i = List->End; i > List->Start + Index; i--)
	{
		List->Array[i] = List->Array[i - 1];
	}
	List->End++;
	List->Used++;
	List->Array[List->Start + Index + 1] = Value;
	return 0;
}

int VecRemoveByIndex(CC_VECTOR *List, int Index)
{
	if (List == NULL)
		return INVALIDPARAMETER1;

	for (int i = List->Start + Index; i < List->End; i++)
	{
		List->Array[i] = List->Array[i + 1];
	}
	List->End--;
	List->Used--;
	return 0;
}

int VecGetCount(CC_VECTOR *List)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}

	return List->Used;
}

int VecClear(CC_VECTOR *List)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}
	free(List->Array);
	List->Used = 0;
	List->Size = 10;
	List->Start = List->Size / 2;
	List->End = List->Size / 2;
}

int VecPartition(int Array[],int Low,int High)
{
	int Pivot = Array[High];
	int Aux;
	int SmallerElement = Low;

	for (int i = Low; i < High; i++)
	{
		if (Array[i] <= Pivot)
		{
			Aux = Array[i];
			Array[i] = Array[SmallerElement];
			Array[SmallerElement] = Aux;
			SmallerElement++;
		}
	}
	Aux = Array[High];
	Array[High] = Array[SmallerElement];
	Array[SmallerElement] = Aux;
	return SmallerElement;
}

int VecQuickSort(int Array[], int Low, int High)
{
	if (Low < High)
	{
		int PartitionIndex = VecPartition(Array, Low, High);
		VecQuickSort(Array, Low, PartitionIndex - 1);
		VecQuickSort(Array, PartitionIndex + 1, High);
	}
}

int VecSort(CC_VECTOR *List)
{
	if (List == NULL)
	{
		return INVALIDPARAMETER1;
	}
	VecQuickSort(List->Array, List->Start, List->End - 1);
	return 0;
}
