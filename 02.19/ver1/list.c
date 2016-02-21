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
	void *index;
	void *head;

	void* (*get)(struct iterator* p);
	struct iterator* (*next)(struct iterator* p);
	struct iterator* (*copy)(struct iterator* p);
	void (*swap)(struct iterator* p, struct iterator* q);
	int (*zeroEqual)(struct iterator* p);
	struct iterator* (*end)(void* p);
	void (*delete)(struct iterator* p);

} Iter;
/*
struct methods{
	void* (*get)(struct list_iter* p);
	struct list_iter* (*next)(struct list_iter* p);
	struct list_iter* (*copy)(struct list_iter* p);
	void (*swap)(struct list_iter* p, struct list_iter* q);
	int (*zeroEqual)(struct list_iter* p);
	struct list_iter* (*end)(void* p);
	void (*delete)(struct list_iter* p);
};*/

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
List *list_insertToBegin(List* p, void *data);
void list_insertTo(Iter * p, void *data);
List *list_insertToEnd(List* p, void *data);
void list_swap(Iter * it_1, Iter * it_2);
void *list_iter_get(Iter * p);
void list_iter_delete(Iter *p);
Iter *list_iter_copy(Iter * p);
Iter* list_iter_methods(Iter* it);


Elem *add_elem()
{
	return calloc(1, sizeof(Elem));
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
	p->index = p->index->prev;
	return p;
}

int list_iter_zeroEqual(Iter * p)
{
	if (p->index->next)
		return 0;
	return 1;
}

Iter *list_iter_next(Iter * p)
{
	p->index = p->index->next;
	return p;
}

Iter *list_iter_begin(List * p)
{
	Iter *it = calloc(1, sizeof(Iter));
	it->index = p->start;
	list_iter_methods(it);
	//printf("it: list_iter_prev %p\n", it->index);
	return it;
}

Iter *list_iter_end(List * p)
{
	Iter *it = list_iter_begin(p);
	for (; !list_iter_zeroEqual(it); list_iter_next(it));
	printf("list_iter_end: %p\n", it->index);
	return it;
}

List *list_create()
{
	List *p = calloc(1, sizeof(List));
	p->start = add_elem();
	printf("it: p->start %p\n", p->start);
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
	Elem *buf = p->index;
	buf->prev->next = buf->next;
	buf->next->prev = buf->prev;
	delete_elem(buf);
}

List *list_insertToBegin(List *p, void *data)
{
	//printf("0it: p->start %p\n", p->start);
	Elem *newElem = add_elem();
	newElem->data = data;
	newElem->next = p->start;
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
	newElem->prev = p->index;
	newElem->next = p->index->next;
	newElem->next->prev = newElem;
	p->index->next = newElem;
}

List *list_insertToEnd(List * p, void *data)
{
	if (p->start->next == NULL) {
		return list_insertToBegin(p, data);
	}
	Iter *it = list_iter_end(p);
	//printf("it: list_iter_end %p\n", it->index);
	list_iter_prev(it);
	//printf("it: list_iter_prev %p\n", it->index);
	list_insertTo(it, data);
	free(it);
	return p;
}

void list_swap(Iter * it_1, Iter * it_2)
{
	void *data_buf = it_1->index->data;
	it_1->index->data = it_2->index->data;
	it_2->index->data = data_buf;
}

void *list_iter_get(Iter * p)
{
	return p->index->data;
}

void list_iter_delete(Iter * p)
{
	free(p);
}

Iter *list_iter_copy(Iter * p)
{
	Iter *it = calloc(1, sizeof(Iter));
	it->index = p->index;
	return it;
}

Iter* list_iter_methods(Iter* it)
{
	it -> get = list_iter_get;
	it -> next = list_iter_next;
	it -> copy = list_iter_copy;
	it -> swap = list_swap;
	return it;
	/*
	(*get)(struct list_iter* p);
	struct list_iter* (*next)(struct list_iter* p);
	struct list_iter* (*copy)(struct list_iter* p);
	void (*swap)(struct list_iter* p, struct list_iter* q);
	int (*zeroEqual)(struct list_iter* p);
	struct list_iter* (*end)(void* p);
	void (*delete)(struct list_iter* p);

	*/
}
