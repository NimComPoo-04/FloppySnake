#include <raylib.h>

#define ASPECT_RATIO 9 / 16

int main(void)
{
	InitWindow(800, ASPECT_RATIO * 800, "...");
	ToggleFullscreen();

	float t = 0;
	Color current = {0};

	Color from = {230, 41, 55, 255};
	Color target = {135, 60, 190, 255};

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
			target.r = GetRandomValue(0, 255);
			target.g = GetRandomValue(0, 255);
			target.b = GetRandomValue(0, 255);
			t = 0;
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
