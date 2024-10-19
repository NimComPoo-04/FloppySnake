#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <raylib.h>
#include "entity.h"

typedef struct snake_node_t
{
	Vector2 position;
	float radius;
	struct snake_node_t *next;
} snake_node_t;

typedef struct
{
	entity_t entity;

	float velocity;
	Vector2 veldir;
	Vector2 oldmouse;

	snake_node_t *head;
	snake_node_t *tail;
} snake_t;

int snake_init(entity_t *e);
int snake_draw(entity_t *e);
int snake_update(entity_t *e);

#endif
