#ifndef _FOOD_H_
#define _FOOD_H_
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
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

extern food_t f[40];
int food_init(entity_t *e);
int food_update(entity_t *e);
int food_draw(entity_t *e);
float VecDistance(Vector2 v1, Vector2 v2); 
int check_food_collision(Vector2 snake_head, float snake_radius); 
#endif
