#include <stdlib.h>
#include <string.h>
#include "scratch_space.h"

typedef struct next_node_t
{
	enum {FREE, ALLOC} status;
	int next;
	int prev;
} next_node_t;

int scratch_space_create(scratch_space_t *s, int initial_size, int es)
{
	s->freelist = -1; 
	s->alloclist = -1;

	return array_create(&s->array, initial_size, es + sizeof(next_node_t));
}

static inline void *get(scratch_space_t *s, int a)
{
	return (s->array.data + a * s->array.element_size);
}

int scratch_space_allocate(scratch_space_t *s, void *d)
{
	if(s->freelist != -1)
	{
		next_node_t *t = get(s, s->freelist);
		int k = t->next;

		next_node_t *g = get(s, s->alloclist);
		g->prev = k;

		t->next = s->alloclist;	
		s->alloclist = s->freelist;

		s->freelist = k;

		t->prev = -1;
		t->status = ALLOC;

		memcpy(((char *)(void *)t + sizeof(next_node_t)), d, s->array.element_size - sizeof(next_node_t));
	}
	else
	{
		array_insert(&s->array, NULL);
		int t = s->array.length - 1;
		next_node_t *k = get(s, t);

		next_node_t *g = get(s, s->alloclist);
		g->prev = t;

		k->next = s->alloclist;
		k->prev = -1;
		k->status = ALLOC;

		s->alloclist = t;

		memcpy((char *)get(s, t) + sizeof(next_node_t), d, s->array.element_size - sizeof(next_node_t));
	}

	return 1;
}

int scratch_space_deallocate(scratch_space_t *s, void *out, int a)
{
	if(a < 0 || a >= s->array.length) return 0;

	next_node_t *t = get(s, a);
	if(t->status != ALLOC) return 0;

	t->status = FREE;

	if(t->prev >= 0)
	{
		next_node_t *n = get(s, t->prev);
		n->next = t->next;
	}
	else
	{
		next_node_t *n = get(s, s->alloclist);
		s->alloclist = n->next;
	}

	if(t->next >= 0)
	{
		next_node_t *n = get(s, t->next);
		n->prev = t->prev;
	}

	t->prev = -1;
	t->next = s->freelist;
	t->status = FREE;

	s->freelist = a;

	if(out)
		memcpy(out, ((char *)(void *)t + sizeof(next_node_t)), s->array.element_size - sizeof(next_node_t));

	return 1;
}

void scratch_space_destroy(scratch_space_t *s)
{
	array_destroy(&s->array);
}
void scratch_space_foreach(scratch_space_t *s, void(*fe)(int id, void *d))
{
	if(s->alloclist == -1) return;

	int id = s->alloclist;
	next_node_t *n = get(s, s->alloclist);

	while(n->next != -1)
	{
		fe(id, (char *)(void *)n + sizeof(next_node_t));

		id = n->next;
		n = get(s, n->next);
	}

	fe(id, (char *)(void *)n + sizeof(next_node_t));
}
