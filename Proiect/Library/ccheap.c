#include <stdlib.h>
#include <stdio.h>

#include "ccheap.h"
#include "errors.h"

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MaxHeap)
	{
		return INVALIDPARAMETER1;
	}
	
	(*MaxHeap) = (CC_HEAP*)malloc(sizeof(CC_HEAP));
	(*MaxHeap)->MinHeap = 0;
	VecCreate(&((*MaxHeap)->Vector));

	if (NULL != InitialElements)
	{
		for (int i = InitialElements->Start; i < InitialElements->End; i++)
		{
			HpInsert(*MaxHeap, InitialElements->Array[i]);
		}
	}
	return 0;
}
int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MinHeap)
	{
		return INVALIDPARAMETER1;
	}
	
	(*MinHeap) = (CC_HEAP*)malloc(sizeof(CC_HEAP));
	(*MinHeap)->MinHeap = 1;
	VecCreate(&((*MinHeap)->Vector));
	if (NULL != InitialElements)
	{
		for (int i = InitialElements->Start; i < InitialElements->End; i++)
		{
			HpInsert(*MinHeap, InitialElements->Array[i]);
		}
	}
	return 0;
}
int HpDestroy(CC_HEAP **Heap)
{
	VecDestroy(&(*Heap)->Vector);
	free(*Heap);
	return 0;
}

int HpSwap(int *A, int *B)
{
	int Aux;
	Aux = (*A);
	(*A) = (*B);
	(*B) = Aux;
	return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	int Poz = Heap->Vector->Used;
	VecInsertHead(Heap->Vector, Value);

	int Child = 0, Parent = 0;
	VecGetValueByIndex(Heap->Vector, Poz, &Child);
	VecGetValueByIndex(Heap->Vector, (Poz - 1) / 2, &Parent);

	if (0 == Heap->MinHeap)
	{
		while ( Child > Parent )
		{
			HpSwap(&Heap->Vector->Array[Heap->Vector->Start + Poz], &Heap->Vector->Array[Heap->Vector->Start + (Poz - 1) / 2]);
			Poz = (Poz - 1) / 2;
			VecGetValueByIndex(Heap->Vector, Poz, &Child);
			VecGetValueByIndex(Heap->Vector, (Poz - 1) / 2, &Parent);
		}
	}
	else
	{
		while ( Child < Parent )
		{
			HpSwap(&Heap->Vector->Array[Heap->Vector->Start + Poz], &Heap->Vector->Array[Heap->Vector->Start + (Poz - 1) / 2]);
			Poz = (Poz - 1) / 2;
			VecGetValueByIndex(Heap->Vector, Poz, &Child);
			VecGetValueByIndex(Heap->Vector, (Poz - 1) / 2, &Parent);
		}
	}

	return 0;
}

int* HpMin(int *A, int *B)
{
	if (*A < *B)
		return A;
	return B;
}

int* HpMax(int *A, int *B)
{
	if (*A > *B)
		return A;
	return B;
}


int HpRemove(CC_HEAP *Heap, int Value)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	int j = 0;
	int ArrayValue = 0;
	int* Parent;
	int* LeftChild;
	int* RightChild;
	int* SelectedChild;
	for (int i = 0; i < Heap->Vector->Used; i++)
	{
		VecGetValueByIndex(Heap->Vector, i, &ArrayValue);
		if (ArrayValue == Value)
		{
			j = i;
			Heap->Vector->Array[Heap->Vector->Start + i] = Heap->Vector->Array[Heap->Vector->End - 1];
			VecRemoveByIndex(Heap->Vector, Heap->Vector->End - 1);
			Parent = &Heap->Vector->Array[Heap->Vector->Start + j];
			LeftChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 1];
			RightChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 2];
			if (Heap->MinHeap)
			{
				SelectedChild = HpMin(LeftChild, RightChild);
				while (*Parent > *SelectedChild  && (j * 2) + 2 < Heap->Vector->Used)
				{
					if (SelectedChild == LeftChild)
					{
						HpSwap(Parent, SelectedChild);
						j = (j * 2) + 1;
					}
					else
					{
						HpSwap(Parent, SelectedChild);
						j = (j * 2) + 2;
					}
					Parent = &Heap->Vector->Array[Heap->Vector->Start + j];
					LeftChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 1];
					RightChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 2];
					SelectedChild = HpMin(LeftChild, RightChild);
				}
				if ((j * 2) + 1 < Heap->Vector->Used && *Parent > *LeftChild)
				{
					HpSwap(Parent, LeftChild);
					j = (j * 2) + 1;
				}
			}
			if (!Heap->MinHeap)
			{
				SelectedChild = HpMax(LeftChild, RightChild);
				while (*Parent < *SelectedChild && (j * 2) + 2 < Heap->Vector->Used)
				{
					if (SelectedChild == LeftChild)
					{
						HpSwap(Parent, SelectedChild);
						j = (j * 2) + 1;
					}
					else
					{
						HpSwap(Parent, SelectedChild);
						j = (j * 2) + 2;
					}
					Parent = &Heap->Vector->Array[Heap->Vector->Start + j];
					LeftChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 1];
					RightChild = &Heap->Vector->Array[Heap->Vector->Start + (j * 2) + 2];
					SelectedChild = HpMax(LeftChild, RightChild);
				}
				if ((j * 2) + 1 < Heap->Vector->Used && *Parent < *LeftChild)
				{
					HpSwap(Parent, LeftChild);
					j = (j * 2) + 1;
				}
			}
			i--;
		}
	}
	return 0;
}
int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	VecGetValueByIndex(Heap->Vector,0,ExtremeValue);
	return 0;
}
int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	HpGetExtreme(Heap, ExtremeValue);
	HpRemove(Heap, *ExtremeValue);
	return 0;
}
int HpGetElementCount(CC_HEAP *Heap)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	return Heap->Vector->Used;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
	if (NULL == Heap)
	{
		return INVALIDPARAMETER1;
	}
	if (NULL == SortedVector)
	{
		return INVALIDPARAMETER2;
	}
	CC_HEAP *AuxHeap;
	int Value;
	if (Heap->MinHeap)
	{
		HpCreateMinHeap(&AuxHeap,Heap->Vector);

		while (AuxHeap->Vector->Start<AuxHeap->Vector->End)
		{
			HpPopExtreme(AuxHeap, &Value);
			VecInsertHead(SortedVector, Value);
		}
		HpDestroy(&AuxHeap);
	}
	else
	{
		HpCreateMaxHeap(&AuxHeap,Heap->Vector);

		while(AuxHeap->Vector->Start<AuxHeap->Vector->End)
		{
			HpPopExtreme(AuxHeap, &Value);
			VecInsertHead(SortedVector, Value);
		}
		HpDestroy(&AuxHeap);
	}
	
	return 0;
}

int HpPrint(CC_HEAP *Heap)
{
	for (int i = Heap->Vector->Start; i < Heap->Vector->End; i++)
	{
		printf("%d ", Heap->Vector->Array[i]);
	}
	printf("\n");
	return 0;
}
