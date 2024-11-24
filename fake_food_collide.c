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
/*int food_init(entity_t *e) {
    food_t *food = (food_t *)e;
    food->center = (Vector2){ GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()) };
    food->radius = 5.0f;  // Food radius
    food->start = GREEN;
    food->end = DARKGREEN;
    food->entity.alive = 1;  // Mark as active
    return 0;
}*/

float VecDistance(Vector2 v1, Vector2 v2) {
    return sqrtf((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

// Check for collision 
int check_food_collision(Vector2 snake_head, float snake_radius, int *score) {
    for (int i = 0; i < FOOD_COUNT; i++) {
        if (food_list[i].entity.alive) {
            float dist = VecDistance(snake_head, food_list[i].center);
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
/*int food_draw(entity_t *e) {
    food_t *food = (food_t *)e;
    if (!food->entity.alive) return 0;  // Skip inactive food
        DrawCircleV(food->center, 5, GREEN); 
    return 0;
}*/

