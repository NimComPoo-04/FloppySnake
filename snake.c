#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include "snake.h"
#include "food.h"

extern food_t f[40];  
int snake_init(entity_t *e)
{
	snake_t *s = (snake_t *)e;

	snake_node_t head = {0};
	
	array_create(&s->body, 100, sizeof(snake_node_t));
	array_insert(&s->body, &head);

	return 0;
}

int snake_draw(entity_t *e)
{
	snake_t *s = (snake_t *)e;

	snake_node_t *n = (snake_node_t *)s->body.data;
	snake_node_t *old = n;

	// float rad = s->radius * 0.1;
	
	Color start = RED;
	Color end = BLUE;

	float t = 1;
	for(int i = 1; i < s->body.length; i++)
	{
		n++;
		// Vector2 v = {old->position.x - n->position.x, old->position.y - n->position.y};

	//	Vector2 k = old->position;
	//	k.x -= v.x / rad;
	//	k.y -= v.y / rad;

		Color current = {0};

		current.r = start.r * (1 - t) + end.r * t;
		current.g = start.g * (1 - t) + end.g * t;
		current.b = start.b * (1 - t) + end.b * t;
		current.a = 255;

		DrawLineBezier(old->position, n->position, s->radius * t, current);
		t -= 1./s->body.length;

		old = n;
	}

	n = (snake_node_t *)s->body.data;
	DrawCircleV(n->position, s->radius * 0.7, PURPLE);

	return 0;
}

int snake_update(entity_t *e)
{
	snake_t *s = (snake_t *)e;

	// EATING CODE
	// ....
	// ....
	//

	static int not_added = 1;
	if (check_food_collision(((snake_node_t *)s->body.data)->position, s->radius)) {
        
		if (not_added) {
            snake_node_t *tail = (snake_node_t *)s->body.data + s->body.length - 1;


            snake_node_t new_segment = {
                .position = tail->position
            };

            // Insert the new segment into the snake's body
            array_insert(&s->body, &new_segment);
            not_added = 0; 
        }
    } else {
		fprintf(stderr,"%d %s /n", __LINE__, __func__);
        not_added = 1; // Reset if no collision
    }

	/*if(IsKeyDown(KEY_SPACE) && not_added)
	{
		snake_node_t tmp = *((snake_node_t *)s->body.data + s->body.length - 1);
		array_insert(&s->body, &tmp);
		not_added = 0;
	}
	else if(IsKeyUp(KEY_SPACE))
	{
		not_added = 1;
	}*/

	snake_node_t *n = (snake_node_t *)s->body.data;

	float dt = GetFrameTime();

	const int w = GetScreenWidth();
	const int h = GetScreenHeight();

	const int x = GetMouseX() - w/2;
	const int y = GetMouseY() - h/2;

	float len = hypot(x, y);

	Vector2 other = n->position;
	other.x += s->velocity * x / len;
	other.y += s->velocity * y / len;

	float t = 1;
	for(int i = 0; i < s->body.length; i++)
	{
		len = hypot((other.x - n->position.x), (other.y - n->position.y));

		if(len - 2 * s->radius * t > 0)
		{
			n->position.x += (other.x - n->position.x) * dt * s->velocity / len;
			n->position.y += (other.y - n->position.y) * dt * s->velocity / len;
		}

		other = n->position;
		n++;

		t -= 1./s->body.length;
	}

	return 0;
}

int snake_dinit(entity_t *e)
{
	snake_t *s = (snake_t *)e;
	array_destroy(&s->body);
	return 0;
}
