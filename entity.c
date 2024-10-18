#include <assert.h>
#include <stdio.h>
#include "entity.h"

/* TODO: For now we are not seprating out entities into sections depending on their bounding box
 * which may be nessesary if there are too many object on screen at the same time. */

// FIXME: remove the memory constraint assert when we start to dynamically allocate entities. 
static inline void freelist_add(entity_list_t *e, int pos)
{	
	assert(e->list_len < MAX_ENT);
	e->freelist[e->list_len++] = pos;
}

// Removing one free spot from list if a free spot is available otherwise failing
static inline int freelist_remove(entity_list_t *e)
{	
	if(e->list_len <= 0)
		return -1;
	return e->freelist[--e->list_len];
}

// Register an entity with the ECS
int entity_list_register(entity_list_t *e, entity_t *x)
{
	int pos = freelist_remove(e);

	if(pos == -1)
	{
		// No free spot is available on the free list, lets try to 
		// get a spot for the rest of the entities array
		assert(e->entities_len < MAX_ENT);

		pos = e->entities_len;
		e->entities_len++;

		e->entities[pos] = x;
	}
	else
	{
		// We found a free spot on the list so we roll with that
		e->entities[pos] = x;
	}

	if(x->init)
		x->init(x);

	x->alive = 1;
	x->id = pos;

	return pos;
}

// Removing elements from the entities
entity_t *entity_list_remove(entity_list_t *e, int pos)
{
	entity_t *t = e->entities[pos];

	// Don't remove is already removed
	if(t == NULL) return NULL;

	// If its the last element reduce the size instead
	// of adding to the free list
	if(pos == e->entities_len - 1)
		e->entities_len--;
	else
		freelist_add(e, pos);

	if(t->dinit)
		t->dinit(t);
	e->entities[pos] = NULL;

	return t;
}

void entity_list_update(entity_list_t *e)
{
	for(int i = 0; i < e->entities_len; i++)
	{
		// Update if the entity exists, has a updater function and is alive
		if(e->entities[i] && e->entities[i]->update && e->entities[i]->alive)
			e->entities[i]->update(e->entities[i]);
	}
}

void entity_list_draw(entity_list_t *e)
{
	for(int i = 0; i < e->entities_len; i++)
	{
		// Draw if the entity exists, has a draw function and is alive
		if(e->entities[i] && e->entities[i]->draw && e->entities[i]->alive)
			e->entities[i]->draw(e->entities[i]);
	}
}

// Dump registered Entities
void entity_dump(entity_list_t *e)
{
	fprintf(stderr, "Registered Entities %d\n", e->entities_len);
	for(int i = 0; i < e->entities_len; i++)
	{
		const entity_t *k = e->entities[i];
		fprintf(stderr, "\t%d %s (%.3f, %.3f, %.3f, %.3f)\n",
				k->id, "dead \0alive" + k->alive * 6,
				k->bounding_box.x, k->bounding_box.y,
				k->bounding_box.width, k->bounding_box.height);
	}

}
