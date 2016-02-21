#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int k = 0;
	List *myList = list_create();
	int array[12] = { };
	for (k = 0; k < 12; k++) {
		array[k] = rand() % 50;
		printf("a[%d] = %d [%p]\n", k, array[k], &array[k]);
	}

	for (k = 0; k < 12; k++) {
		list_insertToEnd(myList, (void *) (array + k));
	}

	Iter *i = list_iter_begin(myList);
	Iter *j;
	printf("\n\n\n");
	for (; !list_iter_zeroEqual(i); list_iter_next(i))
		printf("%d\n", *((int *) list_iter_get(i)));
	list_iter_delete(i);
	printf("\n\n\n");
	for (i = list_iter_begin(myList); !list_iter_zeroEqual(i); list_iter_next(i)) {
		for (j = list_iter_copy(i); !list_iter_zeroEqual(j);
		     list_iter_next(j)) {
			if (*((int *) list_iter_get(i)) >
			    *((int *) list_iter_get(j))) {
				list_swap(i, j);
			}
		}
		list_iter_delete(j);
	}
	list_iter_delete(i);
	i = list_iter_begin(myList);
	for (; !list_iter_zeroEqual(i); list_iter_next(i))
		printf("%d\n", *((int *) list_iter_get(i)));
	//printf("%s\n", (char*)list_iter_get(iter));
	list_iter_delete(i);
	list_delete(myList);

	return 0;
}

/*
yur@virtuozzo.com
*/
