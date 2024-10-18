#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <raylib.h>

#define MAX_ENT 50

// Interface which every entity has to implement.
typedef struct entity_t
{
	int id;
	int alive;

	Rectangle bounding_box;

	int (*init)(struct entity_t *e);
	int (*update)(struct entity_t *e);
	int (*draw)(struct entity_t *e);
	int (*dinit)(struct entity_t *e);
} entity_t;

// Entity List which allows systems to exist
typedef struct entity_list_t
{
	entity_t *entities[MAX_ENT];
	int entities_len;

	int freelist[MAX_ENT];
	int list_len;
} entity_list_t;

int entity_list_register(entity_list_t *e, entity_t *x);
entity_t *entity_list_remove(entity_list_t *e, int);

void entity_list_update(entity_list_t *e);
void entity_list_draw(entity_list_t *e);

void entity_dump(entity_list_t *e);

#endif
