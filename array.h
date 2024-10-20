#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct
{
	char *data;
	int element_size;
	int size;
	int length;
} array_t;

int array_create(array_t *v, int initial_size, int element_size);
int array_insert(array_t *v, void *data);
int array_delete(array_t *v, void *out);
void array_destroy(array_t *v);

#endif
