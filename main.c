#include <raylib.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "scratch_space.h"
#include "particles.h"

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
	.velocity = 1000,
	.head = 0,
	.tail = 0 
};

particles_list_t p = {0};

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

	Camera2D camera = {
		{0, 0},
		{0, 0},
		0,
		1.0f
	};

	particles_list_create(&p, &snake.head->position);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		BeginMode2D(camera);

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

		entity_list_draw(&ent);
		particle_list_draw(&p);

		DrawFPS(snake.head->position.x, snake.head->position.y);
		EndMode2D();
		EndDrawing();

		entity_list_update(&ent);
		particle_list_update(&p);

		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			camera.zoom = 0.5f;
		else
			camera.zoom = 1.0f;

		camera.offset.x = -snake.head->position.x * camera.zoom + GetScreenWidth()/2;
		camera.offset.y = -snake.head->position.y * camera.zoom + GetScreenHeight()/2 ;
	}

	CloseWindow();

	entity_list_destroy(&ent);
	particles_list_destroy(&p);

	return 0;
}
