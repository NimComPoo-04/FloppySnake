#include <stdlib.h>
#include <memory.h>

#include "array.h"

#define BLOC_SIZE 256

int array_create(array_t *v, int initial_size, int element_size)
{
	v->element_size = element_size;
	v->size = initial_size;
	v->length = 0;

	if(initial_size == 0)
		v->data = NULL;
	else
		v->data = calloc(v->size, v->element_size);

	return v->data != NULL;
}

int array_insert(array_t *v, void *data)
{
	if(v->length >= v->size)
	{
		v->size += BLOC_SIZE;
		v->data = realloc(v->data, v->size * v->element_size);

		if(v->data == NULL) return 0;
	}

	if(data)
		memcpy(v->data + v->length * v->element_size, data, v->element_size);
	else
		memset(v->data + v->length * v->element_size, 0, v->element_size);

	v->length++;

	return 1;
}

int array_delete(array_t *v, void *out)
{
	if(v->length <= 0) return 0;

	v->length--;

	if(out) memcpy(out, v->data + v->length * v->element_size, v->element_size);

	if(v->size - v->length >= BLOC_SIZE)
	{
		// Don't clean it out if its the last block
		if(v->size - BLOC_SIZE > 0)
		{
			v->size -= BLOC_SIZE;
			v->data = realloc(v->data, v->size);
		}
	}

	return 1;
}

void array_destroy(array_t *v)
{
	free(v->data);
}
