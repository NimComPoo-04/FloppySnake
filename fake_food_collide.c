#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include "food.h"

/*typedef struct {
    Vector2 position;
    bool active; 
} food_t; */

#define FOOD_COUNT 10
food_t food_list[FOOD_COUNT]; 

// food positions 
int food_init(entity *e) {
    for (int i = 0; i < FOOD_COUNT; i++) {
        food_list[i].center = (Vector2){ GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()) };
        food_list[i].start = CARMINE;
        food_list[i].end = CRIMSON;
        food_list[i].radius=3;
        food_list[i].entity.alive=1;
    }
    return 0;
}

// Check for collision 
int check_food_collision(Vector2 snake_head, float snake_radius, int *score) {
    for (int i = 0; i < FOOD_COUNT; i++) {
        if (food_list[i].entity.alive) {
            float dist = Vector2Distance(snake_head, food_list[i].center);
            if (dist <= snake_radius) { // Collision detected
                // Deactivate the food item and respawn at a new position
                food_list[i].center = (Vector2){ GetRandomValue(snake_head.x-(GetScreenWidth()/2), snake_head.x+(GetScreenWidth()/2)), GetRandomValue(snake_head.y-(GetScreenWidth()/2), snake_head.y+(GetScreenWidth()/2)) };
                food_list[i].entity.alive = 0;  // Food is eaten, deactivate it
                (*score)++; // Increase the score
                return 1; // Collision occurred
            }
        }
    }
    return 0; // No collision
}

// Draw food 
void draw_food(entity_t *e) {
    for (int i = 0; i < FOOD_COUNT; i++) {
        if (food_list[i].entity.alive) {
            DrawCircleV(food_list[i].center, 5, GREEN); // Draw food as a small green circle
        }
    }
    return 0;
}
