#include <stdlib.h>
#include <stdio.h>
#define N 5
#include "container.h"

int main()
{
	int k = 0;
	List *myList = list_create();
	int array[N] = { };
	for (k = 0; k < N; k++) {
		array[k] = rand() % 50;
		printf("a[%d] = %d [%p]\n", k, array[k], &array[k]);
	}

	Iter i = list_iter_begin(myList);
	for (k = 0; k < N; k++) {
		myList->m->iter_insert(&i, (void *) (array + k));
		//list_insertToEnd(myList, (void *) (array + k));
	}

	i = list_iter_begin(myList);
	Iter j = i;
	printf("\n\n\n");
	for (; !myList->m->iter_zeroEqual(i); myList->m->iter_next(&i))
		printf("%d\n", *((int *) myList->m->get(i)));
	printf("\n\n\n");
	for (i = list_iter_begin(myList); !myList->m->iter_zeroEqual(i);
	     myList->m->iter_next(&i)) {
		for (j = i; !myList->m->iter_zeroEqual(j);
		     myList->m->iter_next(&j)) {
			if (*((int *) myList->m->get(i)) >
			    *((int *) myList->m->get(j))) {
				myList->m->iter_swap(&i, &j);
			}
		}
	}
	i = list_iter_begin(myList);
	for (; !myList->m->iter_zeroEqual(i); myList->m->iter_next(&i))
		printf("%d\n", *((int *) myList->m->get(i)));
	//printf("%s\n", (char*)list_iter_get(iter));
	list_delete(myList);

	return 0;
}

/*
yur@virtuozzo.com
*/
