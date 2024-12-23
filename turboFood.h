#ifndef TURBOFOOD_H
#define TURBOFOOD_H
#include "game.h"
tinygl_point_t find_food_position(turbo_t* turbo);
void toggle_food_position(tinygl_point_t food_position, uint8_t set_led);
bool turbo_eat_food (turbo_t* turbo);
void create_food_task(turbo_t* turbo);
#endif