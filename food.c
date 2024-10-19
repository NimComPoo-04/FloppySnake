#include <stdio.h>
#include <math.h>

#include "food.h"


int food_init(entity_t *e)
{
	food_t *f = (food_t *)e;

	// Setting up the bounding box
	e->bounding_box = (Rectangle){
		f->center.x - f->radius, 
		f->center.y - f->radius, 
		f->radius * 2, f->radius * 2
	};

	// Setting up the positional arguments
	int w = GetScreenWidth();
	int h = GetScreenHeight();

	f->center.x = w/2;
	f->center.y = h/2;

	f->target.x = GetRandomValue(f->radius, w - f->radius);
	f->target.y = GetRandomValue(f->radius, h - f->radius);

	// Setting up the colors
	f->start = RED;
	f->end = BLUE;

	// set the animation timer to zero
	f->anim_t = 0;

	return 0;
}

int food_update(entity_t *e)
{
	food_t *f = (food_t *)e;

	e->bounding_box.x = f->center.x - f->radius;
	e->bounding_box.y = f->center.y - f->radius;

	if(f->anim_t <= 1.)
	{
		f->anim_t += GetFrameTime();
	}
	else
	{
		f->anim_t = 0;
		f->center = f->target;
		f->start = f->end;

		int w = GetScreenWidth();
		int h = GetScreenHeight();

		f->target.x = GetRandomValue(f->radius, w - f->radius);
		f->target.y = GetRandomValue(f->radius, h - f->radius);

		f->end.r = GetRandomValue(0, 255);
		f->end.g = GetRandomValue(0, 255);
		f->end.b = GetRandomValue(0, 255);
	}

	return 0;
}

int food_draw(entity_t *e)
{
	food_t *f = (food_t *)e;

	// Color interpolator
	Vector2 v = {0, 0};	
	v.x = f->center.x * (1. - f->anim_t) + f->target.x * f->anim_t;
	v.y = f->center.y * (1. - f->anim_t) + f->target.y * f->anim_t;

	// Color interpolator
	Color k = {0, 0, 0, 10};	
	k.r = f->start.r * (1. - f->anim_t) + f->end.r * f->anim_t;
	k.g = f->start.g * (1. - f->anim_t) + f->end.g * f->anim_t;
	k.b = f->start.b * (1. - f->anim_t) + f->end.b * f->anim_t;

	// Radius

	DrawCircleGradient(v.x, v.y, f->radius, YELLOW, k);

	return 0;
}
