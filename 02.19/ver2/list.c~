/*
list_next
list_get
*next->list_next();
*get_list_get();
*begin...
list_create()
{

	m = malloc();
	m->next=list_next();
	begin=
}

вывод
вставка\удаление
сортировка

	create
	delete
	insert ()
	delet_elem
	get_elem

logo model library
OplenGL
SDL
*/

#include <stdio.h>
#include <stdlib.h>



typedef
    struct listElem {
	void *data;
	struct listElem *prev;
	struct listElem *next;
} Elem;

typedef
    struct list {
	Elem *start;
} List;

typedef
    struct iterator {
	//Elem *index;
	void *indx;
	void *head;

	void *(*get) (struct iterator *);
	struct iterator *(*next) (struct iterator *);
	struct iterator *(*copy) (struct iterator *);
	void (*swap) (struct iterator *, struct iterator *);
	int (*zeroEqual) (struct iterator *);
	struct iterator *(*end) (void *);
	void (*delete) (struct iterator *);

} Iter;

Elem *add_elem();
void delete_elem(Elem * p);
void delete_allElems(Elem * p);
Iter *list_iter_prev(Iter * p);
int list_iter_zeroEqual(Iter * p);
Iter *list_iter_next(Iter * p);
Iter *list_iter_begin(List * p);
Iter *list_iter_end(List * p);
List *list_create();
void list_delete(List * p);
List *list_insertToBegin(List * p, void *data);
void list_insertTo(Iter * p, void *data);
List *list_insertToEnd(List * p, void *data);
void list_swap(Iter * it_1, Iter * it_2);
void *list_iter_get(Iter * p);
void list_iter_delete(Iter * p);
Iter *list_iter_copy(Iter * p);
Iter *list_iter_methods(Iter * it);


Elem *add_elem()
{
	Elem *elem = calloc(1, sizeof(Elem));
	//printf("added elem: %p\n", elem);
	return elem;
}

void delete_elem(Elem * p)
{
	free(p);
	p = NULL;
}

void delete_allElems(Elem * p)
{
	if (p->next != 0)
		delete_allElems(p->next);
	delete_elem(p);
}

Iter *list_iter_prev(Iter * p)
{
	Elem *elem = p->indx;
	//printf("prev1: %p\n", p->indx);
	p->indx = elem->prev;
	//printf("prev2: %p\n", p->indx);
	return p;
}

int list_iter_zeroEqual(Iter * p)
{
	Elem *elem = p->indx;
	//printf("zeroEqual_elem = %p\n", elem);
	if (elem->next == NULL)
		return 1;
	//printf("zeroEqual_elem->next = %p\n", elem->next);
	//if (p->index->next)
	return 0;
}

Iter *list_iter_next(Iter * p)
{
	//printf("before list_iter_next elem = %p\n", p->indx);
	Elem *elem = p->indx;
	//printf("wait list_iter_next elem = %p\n", elem->next);
	p->indx = elem->next;
	//printf("after list_iter_next elem = %p\n", p->indx);
	//p->index = p->index->next;
	return p;
}

Iter *list_iter_begin(List * p)
{
	Iter *it = calloc(1, sizeof(Iter));
	//it->index = p->start;
	it->indx = p->start;
	list_iter_methods(it);
	//printf("it: list_iter_prev %p\n", it->index);
	return it;
}

Iter *list_iter_end(List * p)
{
	Iter *it = list_iter_begin(p);
	for (; !list_iter_zeroEqual(it); list_iter_next(it));
	//printf("LOOP ENDED\n");
	//Elem* elem = it->indx;
	//printf("Last: %p\n", it->indx);
	//printf("Last-prev: %p\n", elem->prev);        
	//if(elem != NULL)
	//      printf("Last-next: %p\n", elem->next);
	return it;
}

List *list_create()
{
	List *p = calloc(1, sizeof(List));
	p->start = add_elem();
	//printf("it: p->start %p\n", p->start);
	p->start->prev = NULL;
	p->start->next = NULL;
	p->start->data = NULL;
	return p;
}

void list_delete(List * p)
{
	delete_allElems(p->start);
	free(p);
}

void list_elem_delete(Iter * p)
{
	Elem *buf = p->indx;
	buf->prev->next = buf->next;
	buf->next->prev = buf->prev;
	delete_elem(buf);
}

List *list_insertToBegin(List * p, void *data)
{
	//printf("0it: p->start %p\n", p->start);
	Elem *newElem = add_elem();
	newElem->data = data;

	newElem->next = p->start;
	newElem->prev = NULL;
	p->start->prev = newElem;
	p->start = newElem;
	//printf("1it: p->start %p\n", p->start);
	//printf("1it: p->start->next %p\n", p->start->next);
	//printf("1it: p->start->next->prev %p\n", p->start->next->prev);
	return p;
}

void list_insertTo(Iter * p, void *data)
{
	Elem *newElem = add_elem();
	newElem->data = data;
	//if(p->index->next == NULL)
	Elem *elem = p->indx;
	//printf("TOelement %p\n", elem);
	elem->prev->next = newElem;
	newElem->prev = elem->prev;
	newElem->next = elem;
	elem->prev = newElem;
	p->indx = elem;
}

List *list_insertToEnd(List * p, void *data)
{
	//printf("p->start[%p]->next = %p\n",p->start, p->start->next);
	if (p->start->next == NULL) {
		return list_insertToBegin(p, data);
	}
	Iter *it = list_iter_end(p);
	//printf("it: list_iter_end %p\n", it->indx);
	//Elem* elem = it -> indx;
	//printf("it: list_iter_end->next %p\n", elem->next);
	//printf("it: list_iter_end->prev %p\n", elem->prev);
	//list_iter_prev(it);
	//printf("it: list_iter_prev %p\n", it->indx);
	list_insertTo(it, data);
	free(it);
	return p;
}

void list_swap(Iter * it_1, Iter * it_2)
{
	Elem *elem1 = it_1->indx;
	Elem *elem2 = it_2->indx;
	void *data_buf = elem1->data;
	elem1->data = elem2->data;
	elem2->data = data_buf;
	it_1->indx = elem1;
	it_2->indx = elem2;
}

void *list_iter_get(Iter * p)
{
	Elem *elem = p->indx;
	return elem->data;
}

void list_iter_delete(Iter * p)
{
	free(p);
}

Iter *list_iter_copy(Iter * p)
{
	Iter *it = calloc(1, sizeof(Iter));
	it->indx = p->indx;
	list_iter_methods(it);
	return it;
}

Iter *list_iter_methods(Iter * it)
{
	it->get = list_iter_get;
	it->next = list_iter_next;
	it->copy = list_iter_copy;
	it->swap = list_swap;
	it->zeroEqual = list_iter_zeroEqual;
	it->delete = list_iter_delete;
	return it;
}
