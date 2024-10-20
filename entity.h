#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <raylib.h>

#include "scratch_space.h"

// Interface which every entity has to implement.
typedef struct entity_t
{
	int alive;

	int (*init)(struct entity_t *e);
	int (*update)(struct entity_t *e);
	int (*draw)(struct entity_t *e);
	int (*dinit)(struct entity_t *e);
} entity_t;

// Entity List which allows systems to exist
typedef struct entity_list_t
{
	scratch_space_t entities;
} entity_list_t;

int entity_list_create(entity_list_t *e);
void entity_list_destroy(entity_list_t *e);

int entity_list_register(entity_list_t *e, entity_t *x);
entity_t *entity_list_remove(entity_list_t *e, int pos);

void entity_list_update(entity_list_t *e);
void entity_list_draw(entity_list_t *e);

#endif
