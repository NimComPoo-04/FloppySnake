#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <raylib.h>
#include "entity.h"
#include "array.h"

typedef struct snake_node_t
{
	Vector2 position;
} snake_node_t;

typedef struct
{
	entity_t entity;

	float velocity;
	float radius;			// the head radius

	array_t body;
} snake_t;

int snake_init(entity_t *e);
int snake_dinit(entity_t *e);
int snake_draw(entity_t *e);
int snake_update(entity_t *e);

#endif
