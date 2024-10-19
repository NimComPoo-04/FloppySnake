#include <raylib.h>

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

int main(void)
{
	entity_list_t ent = {0};

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

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
