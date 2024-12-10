#include <stdio.h>
#include <math.h>

#include "food.h"


int score=0;
int food_init(entity_t *e)
{
	food_t *f = (food_t *)e;
    f->center = (Vector2){GetRandomValue(100, GetScreenWidth() - 100), 
                             GetRandomValue(100, GetScreenHeight() - 100)};
    f->radius = GetRandomValue(20, 25);  // Random size for food
	e->alive=1;
	return 0;
}
int food_update(entity_t *e)
{
	food_t *f = (food_t *)e;

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

		//FIXME
		f->target.x = GetRandomValue(f->radius, w - f->radius)*5;
		f->target.y = GetRandomValue(f->radius, h - f->radius)*5;

		f->end.r = GetRandomValue(0, 255);
		f->end.g = GetRandomValue(0, 255);
		f->end.b = GetRandomValue(0, 255);
	}
	return 0;
}

 

float VecDistance(Vector2 v1, Vector2 v2) {
    return sqrtf((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

// Check for collision 
food_t f[40]; 
int check_food_collision(Vector2 snake_head, float snake_radius) {
    for (int i = 0; i < 40; i++) {
        if (f[i].entity.alive) 
		{
            float dist = VecDistance(snake_head, f[i].center);
            if (dist <= snake_radius + f[i].radius+2){ 
				printf("Food eaten! Respawning at new location...\n"); // Collision detected
                f[i].entity.alive = 0; // Deactivate the food item and respawn at a new position
                //f[i].center = (Vector2){ GetRandomValue(snake_head.x-(GetScreenWidth()/2), snake_head.x+(GetScreenWidth()/2)), GetRandomValue(snake_head.y-(GetScreenWidth()/2), snake_head.y+(GetScreenWidth()/2)) };
                f[i].center.x = GetRandomValue(f[i].radius, GetScreenWidth() - f[i].radius)+snake_head.x;
				f[i].center.y = GetRandomValue(f[i].radius, GetScreenHeight() - f[i].radius)+snake_head.y;
				f[i].entity.alive = 1;  // Food is eaten, deactivate it
                (score)++; // Increase the score
                return 1; // Collision occurred
            }
        }
    }
    return 0; // No collision
}

int food_draw(entity_t *e)
{
	food_t *f = (food_t *)e;

	// Color interpolator
	Vector2 v = {0, 0};	
	v.x = f->center.x * (1. - f->anim_t) + f->target.x * f->anim_t;
	v.y = f->center.y * (1. - f->anim_t) + f->target.y * f->anim_t;

	// Color interpolator
	/*Color k = {0, 0, 0, 10};	
	k.r = f->start.r * (1. - f->anim_t) + f->end.r * f->anim_t;
	k.g = f->start.g * (1. - f->anim_t) + f->end.g * f->anim_t;
	k.b = f->start.b * (1. - f->anim_t) + f->end.b * f->anim_t;*/

	// Radius

	//DrawCircleGradient(v.x, v.y, f->radius, YELLOW, k);
	DrawCircle(v.x, v.y, f->radius, YELLOW);

	return 0;
}
