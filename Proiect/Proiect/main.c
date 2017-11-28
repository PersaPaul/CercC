#include <stdio.h>
#include <stdlib.h>
#include "ccheap.h"

int main()
{
	CC_HEAP *heap;
	HpCreateMinHeap(&heap,NULL);
	HpInsert(heap, 5);
	HpInsert(heap, 7);
	HpInsert(heap, 8);
	HpInsert(heap, 9);
	HpInsert(heap, 43);
	HpInsert(heap, 43);
	HpInsert(heap, 43);
	HpInsert(heap, 43);
	HpInsert(heap, 1);
	printf("%d\n",HpGetElementCount(heap));
	HpPrint(heap);
	int a;
	CC_VECTOR *x;
	VecCreate(&x);
	HpSortToVector(heap, x);
	printf("\n");
	for (int i = x->Start; i < x->End; i++)
	{
		printf("%d ", x->Array[i]);
	}

	return 0;
}