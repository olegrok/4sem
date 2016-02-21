#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#define N 5
int main()
{
	int k = 0;
	List *myList = list_create();
	int array[N] = { };
	for (k = 0; k < N; k++) {
		array[k] = rand() % 50;
		printf("a[%d] = %d [%p]\n", k, array[k], &array[k]);
	}

	for (k = 0; k < N; k++) {
		list_insertToEnd(myList, (void *) (array + k));
	}

	Iter *i = list_iter_begin(myList);
	Iter *j;
	printf("\n\n\n");
	for (; !i->zeroEqual(i); i->next(i))
		printf("%d\n", *((int *) i->get(i)));
	i->delete(i);
	printf("\n\n\n");
	for (i = list_iter_begin(myList); !i->zeroEqual(i); i->next(i)) {
		for (j = i->copy(i); !j->zeroEqual(j); j->next(j)) {
			if (*((int *) i->get(i)) > *((int *) j->get(j))) {
				i->swap(i, j);
			}
		}
		j->delete(j);
	}
	i->delete(i);
	i = list_iter_begin(myList);
	for (; !i->zeroEqual(i); i->next(i))
		printf("%d\n", *((int *) i->get(i)));
	//printf("%s\n", (char*)list_iter_get(iter));
	i->delete(i);
	list_delete(myList);

	return 0;
}

/*
yur@virtuozzo.com
*/
