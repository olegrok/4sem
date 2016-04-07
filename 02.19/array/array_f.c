#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array_iter.h"

struct array{
	void ** arr;
	int max_N;
	int cur_N;	//last num with data
};	//Array

struct iter_array
{
	int num;
}; //Iter

Array double_max(Array p);
Array copy_from(Array p, int k, int l);
void copy_forward(Array p, int k);
void copy_back(Array p, int k);

Array array_create(int N)	//creates new array
{
	Array p = malloc(sizeof(struct array));
	p->max_N = N;
	p->arr = malloc(sizeof(void *) * p->max_N);
	p->cur_N = 0;
	return p;
}

void array_delete(Array p)	//delete array
{
	free(p->arr);
	free(p);
}

void array_insert_k(Array p, int k, void  *data)	//put data to arr[k] and move other data right
{
	if (k >= p->cur_N + 1)
		array_insert_last(p, data);
	else
		{
			copy_forward(p, k);
	//		strcpy(p->arr[k], data);
			p->arr[k] = data;
		}
}

void array_insert_last(Array p, void *data)	//put data to last available position in array
{
	if (p->cur_N < p->max_N - 1)
		{
	//	strcpy(p->arr[p->cur_N+1], data);
		p->arr[p->cur_N+1] = data;
		p->cur_N += 1;
		}
	else
		{
		p = double_max(p);
		strcpy(p->arr[p->cur_N+1], data);
		p->cur_N +=1;
		}
}

void array_insert_first(Array p, void *data)	//put data to first (zero) position in array
{
	array_insert_k(p, 0, data);
}

void array_delete_k(Array p, int k)	//delete data from arr[k] and move other data left
{
	copy_back(p, k);
}

void array_delete_last(Array p)	//delete data from last position in array
{
	p->arr[p->cur_N] = NULL;
}

void array_delete_first(Array p)	//delete data from first (zero) position in array and move other data left
{
	array_delete_k(p, 0);
}

void array_get_k(Array p, int k)	//takes data from arr[k]
{
	void* data = malloc(sizeof(p->arr[k]));

	strcpy(data, p->arr[k]);
}

Array double_max(Array p)		//doubles max_N
{
	int i;

	Array newp = array_create(p->max_N * 2);
	newp->cur_N = p->cur_N;

	for(i = 0; i <= p->cur_N; i++)
		newp->arr[i]= p->arr[i];

	array_delete(p);
	return newp;
}

Array copy_from(Array p, int k, int l)	//copies data from p[k]-p[l] to another array
{
	Array tmp = array_create(p->max_N);

	int i;
	for(i = k; i<= l; i++)
		tmp[i] = p[i];

	return tmp;
}

void copy_forward(Array p, int k)	// copies data one box to the right from k position
{
	if(p->cur_N = p->max_N - 1)
		double_max(p);

	int i;
	for(i = p->cur_N; i>=k; i--)
		p[i+1] = p[i];	//which variant is better???? what if data type is char*?
	//	strcpy(p[i+1], p[i]);
}

void copy_back(Array p, int k)	// copies data one box to the left to k position
{
	int i;
	for(i = k+1; i < p->max_N; i++)
		p[i-1] = p[i];
		//strcpy(p[i-1], p[i]);
}

void array_print(Array p)
{
	int i;

	for(i = 0; i < p->cur_N; i++)
		printf("%p\n", p->arr[i]);
}


