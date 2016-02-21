#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 15

typedef
struct shape
{
	double x, y, z, color;
	char* form;
	struct shape* child;
} Shape;


Shape * shape_init()
{
	Shape * p = calloc(1, sizeof(Shape));
	if(p == NULL)
		return NULL;
	p->child = NULL;
	p->form = calloc(size, 1);
	strncpy(p->form, "point", size);
	return p;
}

Shape * shape_initWithValue(double x, double y, double z, char * form)
{
	Shape * p = shape_init();
	if(p == NULL)
		return NULL;
	p -> x = x;
	p -> y = y;
	p -> z = z;	
	if(form != NULL)
		strncpy(p -> form, form, size);
	return p;
}

void shape_delete(Shape * p)
{
	if(p -> child)
		shape_delete(p->child);
	free(p -> form);
	free(p);

}

void shape_moveAbsolute(Shape * p, double x, double y, double z)
{
	p -> x = x;
	p -> y = y;
	p -> z = z;
	if(p->child)
		shape_moveAbsolute(p->child, p->x, p->y, p->z);

}

void shape_moveRelative(Shape * p, double x, double y, double z)
{
	p -> x += x;
	p -> y += y;
	p -> z += z;
	if(p->child)
		shape_moveAbsolute(p->child, p->x, p->y, p->z);
}

void shape_setInside(Shape * p, Shape * child)
{
	
	shape_moveAbsolute(child, p -> x, p -> y, p -> z);
	p->child = child;
}

void shape_transform(Shape * p, char * newForm)
{
	if(newForm != NULL)
		strncpy(p -> form, newForm, size);
}

void shape_print(Shape * p)
{
	printf("Hello! I'm %s\n", p -> form);
	printf("I live in (%.1f,%.1f,%.1f)", p->x, p->y, p->z);
	if(p->child != NULL)
	{
		printf("\nMy child:	\n{\n");
		shape_print(p->child);
		printf("}");
	}
	printf("\n");
}


