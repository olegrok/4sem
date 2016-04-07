typedef struct array * Array;
typedef struct iter_array *Iter;

Array array_create(int N);	//creates new array
void array_delete(Array p);	//delete array
void array_insert_k(Array p, int k, void *data);	//put data to arr[k] and move other data right
void array_insert_last(Array p, void *data);	//put data to last available position in array
void array_insert_first(Array p, void *data);	//put data to first (zero) position in array
void array_delete_k(Array p, int k);	//delete data from arr[k] and move other data left
void array_delete_last(Array p);	//delete data from last position in array
void array_delete_first(Array p);	//delete data from first (zero) position in array and move other data left
void array_get_k(Array p, int k);	//takes data from arr[k]
void array_print(Array p);	//print all array