#include <assert.h>
#include <stdio.h>

#include "entity.h"

int entity_list_create(entity_list_t *e)
{
	return scratch_space_create(&e->entities, 30, sizeof(entity_t *));
}

void entity_list_destroy(entity_list_t *e)
{
	scratch_space_destroy(&e->entities);
}

// Register an entity with the ECS
int entity_list_register(entity_list_t *e, entity_t *x)
{
	if(x->init)
		x->init(x);
	int d = scratch_space_allocate(&e->entities, &x);
	return d;
}

// Removing elements from the entities
entity_t *entity_list_remove(entity_list_t *e, int pos)
{
	entity_t *out  = NULL;
	scratch_space_deallocate(&e->entities, &out, pos);
	if(out && out->dinit)
		out->dinit(out);
	return out;
}

static void feu(int id, void *d)
{
	(void)id;
	entity_t *e = *(entity_t **)d;
	if(e->update)
		e->update(e);
}

static void fed(int id, void *d)
{
	(void)id;
	entity_t *e = *(entity_t **)d;
	if(e->draw)
		e->draw(e);
}

void entity_list_update(entity_list_t *e)
{
	scratch_space_foreach(&e->entities, feu);
}

void entity_list_draw(entity_list_t *e)
{
	scratch_space_foreach(&e->entities, fed);
}
