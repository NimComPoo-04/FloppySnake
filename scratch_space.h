#ifndef _SCRATCH_SPACE_H_
#define _SCRATCH_SPACE_H_

// NOTE: Do not use this if the size of the allocations before hand.
// it won't crash but won't be fast aswell.

#include "array.h"

typedef struct
{
	array_t array;
	int freelist;
	int alloclist;
} scratch_space_t;

int scratch_space_create(scratch_space_t *s, int initial_size, int element_size);

int scratch_space_allocate(scratch_space_t *s, void *d);
int scratch_space_deallocate(scratch_space_t *s, void *out, int a);

void scratch_space_destroy(scratch_space_t *s);

void scratch_space_foreach(scratch_space_t *s, void(*fe)(int id, void *d));

#endif
