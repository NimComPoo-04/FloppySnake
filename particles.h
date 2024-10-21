#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "scratch_space.h"

typedef struct
{
	float t;		// lifetime
	float dt;		// how much it dies each frame

	Color color;
	float radius;

	int count;		// number of particles

	Vector2 *origin;
	Vector2 veldir;
	float velocity;
} particles_t;

typedef scratch_space_t particles_list_t;

int particles_list_create(particles_list_t *p, Vector2 *origin);
void particle_list_update(particles_list_t *e);
void particle_list_draw(particles_list_t *e);
int particles_list_destroy(particles_list_t *p);

#endif
