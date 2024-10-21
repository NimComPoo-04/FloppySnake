#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "particles.h"

static void ini(int id, void *v)
{
	(void)id;
	particles_t *p = v;

	float theta = 2 * 3.1416 * GetRandomValue(0, 1000) / 1000;
	p->veldir.x = cos(theta);
	p->veldir.y = sin(theta);

	p->velocity = GetRandomValue(100, 200);
	p->dt = 3;

	p->color.r = GetRandomValue(0, 255);
	p->color.g = GetRandomValue(0, 255);
	p->color.b = GetRandomValue(0, 255);

	p->radius = GetRandomValue(5, 15);
	p->t = 0;
}

int particles_list_create(particles_list_t *p, Vector2 *origin)
{
	scratch_space_create(p, 50, sizeof(particles_t));

	particles_t pe = {0};
	pe.origin = origin;

	for(int i = 0; i < 100; i++)
		scratch_space_allocate(p, &pe);

	scratch_space_foreach(p, ini);
	return 0;
}

static void feu(int id, void *k)
{
	particles_t *p = k;
	float dt = GetFrameTime();
	p->t += dt * p->dt; 
	if(p->t > 1)
		ini(id, p);
	p->color.a = 255 * (1 - p->t); 
}

static void fed(int id, void *k)
{
	(void)id;
	particles_t *p = k;

	Vector2 current = {
		p->origin->x + p->veldir.x * p->t * p->velocity,
		p->origin->y + p->veldir.y * p->t * p->velocity,
	};

	DrawCircleV(current, p->radius, p->color);
}

void particle_list_update(particles_list_t *e)
{
	scratch_space_foreach(e, feu);
}

void particle_list_draw(particles_list_t *e)
{
	scratch_space_foreach(e, fed);
}

int particles_list_destroy(particles_list_t *p)
{
	scratch_space_destroy(p);
	return 0;
}
