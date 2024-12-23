#include <stdlib.h>
#include <stdint.h>
#include "tinygl.h"
#include "turboFood.h"
#include "game.h"


tinygl_point_t food_pos;

/** Finds the display position */
tinygl_point_t find_food_position(turbo_t* turbo)
{
    // Initialise the food 
    tinygl_point_t food_position;
    food_position.x = rand() % 5;
    food_position.y = rand() % 7;

    for (size_t i = 0; i < turbo->turboLen; i++) {
        while ((turbo->body[i].pos.x == food_position.x) && (turbo->body[i].pos.y == food_position.y)) {
            food_position.x = rand() % 5;
            food_position.y = rand() % 7;
        }
    }
    
    return food_position;
}


bool turbo_eat_food (turbo_t* turbo) 
{
    if (turbo->body[0].pos.x == food_pos.x && turbo->body[0].pos.y == food_pos.y) {
        return true;
    } else {
        return false;
    }
}

void create_food_task(turbo_t* turbo)
{
    // turbo_t* turbo = data;
    food_pos = find_food_position(turbo);
    tinygl_draw_point (food_pos, 1);
}
