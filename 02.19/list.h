#ifndef MYLIST_H
#define MYLIST_H

typedef struct  list List;
typedef struct iterator Iter;

typedef
    struct iterator {
	//Elem *index;
	void *indx;
	void *head;

	void*(*get)(struct iterator*);
	struct iterator* (*next)(struct iterator*);
	struct iterator* (*copy)(struct iterator*);
	void (*swap)(struct iterator*, struct iterator*);
	int (*zeroEqual)(struct iterator*);
	struct iterator* (*end)(void*);
	void (*delete)(struct iterator*);

} Iter;

List* list_create();
void list_delete(List* p);
List* list_insertToBegin(List *p, void *data);
List* list_insertToEnd(List *p, void *data);

void* list_iter_get(Iter* p);
Iter* list_iter_begin(List* p);
Iter* list_iter_next(Iter* p);
Iter* list_iter_copy(Iter* p);
void list_swap(Iter* p, Iter* q);

int list_iter_zeroEqual(Iter* p);
Iter* list_iter_end(List* p);
void list_iter_delete(Iter* p);

#endif