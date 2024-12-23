#ifndef TURBO_H
#define TURBO_H
#include "game.h"

void kill_turbo(turbo_t* turbo);
void game_over(turbo_t* turbo, tinygl_point_t next_head_pos);
void turbo_move_straight_task (void *data);
void grow_snake(turbo_t* turbo);
void turbo_move (int direction, turbo_t* turbo);
tinygl_point_t get_next_pos(turbo_t* turbo, tinygl_point_t current_pos);
void draw_points(turbo_t* turbo);

#endif