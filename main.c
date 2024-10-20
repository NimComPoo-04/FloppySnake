#include <raylib.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "scratch_space.h"

#include "entity.h"
#include "snake.h"
#include "food.h"

#define ASPECT_RATIO 9 / 16

#define FOOD_COUNT 40
static food_t f[FOOD_COUNT] = {0};

snake_t snake = {
	.entity = {
		.init = snake_init,
		.update = snake_update,
		.draw = snake_draw
	},
	.velocity = 800,
	.head = 0,
	.tail = 0 
};

/*
void fe(int id, void *d)
{
	char *k = d;
	printf("%d : %s\n", id, k);
}
*/

int main(void)
{
	entity_list_t ent = {0};
	entity_list_create(&ent);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
	InitWindow(0, 0, "...");

	for(int i = 0; i < FOOD_COUNT; i++)
	{
		f[i].entity.init = food_init;
		f[i].entity.update = food_update;
		f[i].entity.draw= food_draw;

		f[i].radius = GetRandomValue(20, 40);

		entity_list_register(&ent, &f[i].entity);
	}

	entity_list_register(&ent, &snake.entity);

	float t = 0;
	Color current = {0};

	Color from = {0};
	Color target = {0};

	while(!WindowShouldClose())
	{
		BeginDrawing();

		current.r = from.r * (1 - t) + target.r * t;
		current.g = from.g * (1 - t) + target.g * t;
		current.b = from.b * (1 - t) + target.b * t;

		ClearBackground(current);
	
		t += GetFrameTime();
		if(t >= 1)
		{
			from = target;
			target.r = GetRandomValue(0, 128/2);
			target.g = GetRandomValue(0, 128/2);
			target.b = GetRandomValue(0, 128/2);
			t = 0;
		}

		entity_list_update(&ent);
		entity_list_draw(&ent);

		DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();

	/*
	scratch_space_t s;
	
	char names[50];
	scratch_space_create(&s, 256, 50);

	strcpy(names, "hello");
	scratch_space_allocate(&s, names);
	strcpy(names, "funny");
	scratch_space_allocate(&s, names);
	strcpy(names, "you are");
	scratch_space_allocate(&s, names);
	strcpy(names, "not dawg");
	scratch_space_allocate(&s, names);

	assert(scratch_space_deallocate(&s, 0, 3));

	strcpy(names, "something");
	scratch_space_allocate(&s, names);

	strcpy(names, "djfks");
	scratch_space_allocate(&s, names);

	assert(scratch_space_deallocate(&s, 0, 4));

	scratch_space_foreach(&s, fe);
	*/

	entity_list_destroy(&ent);

	return 0;
}
