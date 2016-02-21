#include "shape.h"
int main()
{
	Shape * example = shape_init();
	shape_print(example);
	shape_delete(example);
	example = shape_initWithValue(1, 2, 3, "cube");
	shape_print(example);
	shape_transform(example, "sphere");
	shape_moveAbsolute(example, 4, 5, 6);
	shape_print(example);
	Shape * child = shape_init();
	shape_setInside(example, child);
	shape_print(example);
	Shape * child2 = shape_initWithValue(100, 100, 100, "point2");
	shape_setInside(child, child2);
	shape_moveRelative(example, 1, 1, 1);
	shape_print(example);
	shape_delete(example);
	return 0;
}