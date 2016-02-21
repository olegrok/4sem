#ifndef MYLIST_H
#define MYLIST_H

typedef struct  list List;
typedef struct list_iter Iter;

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