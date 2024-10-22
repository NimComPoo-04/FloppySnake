#ifndef _FOOD_H_
#define _FOOD_H_

#include "entity.h"

// Position
// Color
// Opacity
// Random Movement
// Mass -> score

typedef struct
{
	entity_t entity;

	float radius;

	Vector2 center;
	Vector2 target;

	Color start;
	Color end;
	float anim_t;
} food_t;

int food_init(entity_t *e);
int food_update(entity_t *e);
int food_draw(entity_t *e);

#endif
