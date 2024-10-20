#include "snake.h"

#include <raylib.h>
#include <raymath.h>

#define SNAKE_NODES 20
static snake_node_t snake_nodes[SNAKE_NODES] = {0};

int snake_init(entity_t *e)
{
	snake_t *s = (snake_t *)e;
	
	s->head = snake_nodes;
	snake_node_t *n = s->head;

	for(int i = 1; i < SNAKE_NODES; i++, n = n->next)
	{
		n->next = snake_nodes + i;
		n->radius = 30;
		n->position.x = GetRandomValue(0, GetScreenWidth());
		n->position.y = GetRandomValue(0, GetScreenHeight());
	}

	return 0;
}

int snake_draw(entity_t *e)
{
	snake_t *s = (snake_t *)e;

	snake_node_t *n = s->head;
	snake_node_t *old = n;
	n = n->next;

	float rad = n->radius * 0.1;

	while(n)
	{
		Vector2 v = {old->position.x - n->position.x, old->position.y - n->position.y};

		Vector2 k = old->position;
		k.x -= v.x / rad;
		k.y -= v.y / rad;

		DrawLineEx(k, n->position, n->radius, RED);                   // Draw line segment cubic-bezier in-out interpolation
		old = n;
		n = n->next;
	}

	return 0;
}

int snake_update(entity_t *e)
{
	snake_t *s = (snake_t *)e;

	snake_node_t *n = s->head;

	float dt = GetFrameTime();

	Vector2 other;
	other.x = GetMouseX();
	other.y = GetMouseY();

	float len = hypot(s->oldmouse.x - other.x, s->oldmouse.y - other.y);

	if(len < n->radius)
	{
		other.x = n->position.x + s->veldir.x;
		other.y = n->position.y + s->veldir.y;
	}
	else
	{
		len = hypot((other.x - n->position.x), (other.y - n->position.y));

		s->veldir.x = (other.x - n->position.x) / len * s->velocity;
		s->veldir.y = (other.y - n->position.y) / len * s->velocity;

		s->oldmouse = other;
	}

	while(n)
	{
		len = hypot((other.x - n->position.x), (other.y - n->position.y));

		if(len - 2 * n->radius > 0)
		{
			n->position.x += (other.x - n->position.x) * dt * s->velocity / len;
			n->position.y += (other.y - n->position.y) * dt * s->velocity / len;
		}

		other = n->position;

		n = n->next;
	}

	return 0;
}
