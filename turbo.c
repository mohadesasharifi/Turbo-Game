/** @file   turbo.c
    @author Mohadesa
    @date   13 Oct 2021
    @brief  turbo moves here.*/

#include <stdio.h>
#include <stdlib.h>
#include "tinygl.h"
#include "game.h"
#include "task.h"
#include "buttonControl.h"
#include "demo.h"
#include "turboFood.h"
uint16_t score = 0;

tinygl_point_t get_next_pos(tinygl_point_t current, int direction)
{
    tinygl_point_t next_pos;
    if (direction == 0) {
        next_pos = tinygl_point ((current.x + 0) % 5, (current.y - 1 + 7) % 7);
    }
    else if (direction == 2) {
        next_pos = tinygl_point ((current.x + 0) % 5, (current.y + 1) % 7);
    }

    else if (direction == 3) {
        next_pos = tinygl_point ((current.x - 1 + 5) % 5, (current.y + 0) % 7);
    }
    else if (direction == 1) {
        next_pos = tinygl_point ((current.x + 1) % 5, (current.y + 0) % 7);
    }

    return next_pos;
}

void kill_turbo(turbo_t* turbo)
{
    for (size_t i = 0; i < turbo->turboLen; i++) {
        turbo->body[i].pos.x = -1;
        turbo->body[i].pos.y = -1;
        turbo->body[i].dir = -1;
    }
    turbo->turboLen = 0;
    turbo->alive = 0;
}


void game_over(turbo_t* turbo, tinygl_point_t next_head_pos) 
{
    for (size_t i = 1; i < turbo->turboLen; i++) {
        if (next_head_pos.x == turbo->body[i].pos.x && next_head_pos.y == turbo->body[i].pos.y) {
            // kill_turbo(turbo); 
            turbo->alive = 0;
            demo_game_over();          
        } 
    }
}

void grow_snake(turbo_t* turbo)
{
    enum dir direction = turbo->body[turbo->turboLen-1].dir;
    bulb_t segment;
    if (direction == S) {
        segment.pos.x = turbo->body[turbo->turboLen-1].pos.x;
        segment.pos.y = (turbo->body[turbo->turboLen-1].pos.y - 1);
    } 
    if (direction == N) {
        segment.pos.x = turbo->body[turbo->turboLen-1].pos.x;
        segment.pos.y = (turbo->body[turbo->turboLen-1].pos.y + 1);
    }
    if (direction == W) {
        segment.pos.x = turbo->body[turbo->turboLen-1].pos.x + 1;
        segment.pos.y = (turbo->body[turbo->turboLen-1].pos.y);
    }
    if (direction == E) {
        segment.pos.x = turbo->body[turbo->turboLen-1].pos.x - 1;
        segment.pos.y = (turbo->body[turbo->turboLen-1].pos.y);
    }
    
    segment.dir = turbo->body[turbo->turboLen-1].dir;
    turbo->body[turbo->turboLen] = segment;  
    tinygl_draw_point (turbo->body[turbo->turboLen].pos, 1);  
    turbo->turboLen++;
}


void turbo_move (int direction, turbo_t* turbo)
{ 
    if ((direction == 1 && turbo->body[0].dir == W) ||
        (direction == 3 && turbo->body[0].dir == E) ||
        (direction == 2 && turbo->body[0].dir == N) ||
        (direction == 0 && turbo->body[0].dir == S)) {

        // Ignore turbo running back into himself.
        return;
    }
    tinygl_point_t current_head = get_next_pos(turbo->body[0].pos, direction);

    //check for gameover first
    game_over(turbo, current_head);
    

    //turn off previous positions that turbo left
    for(uint8_t i = 0; i < turbo->turboLen; i++) {
        tinygl_draw_point (turbo->body[i].pos, 0);
        
    }
    
    //turn on next position turbo move in to
    for(uint8_t i = turbo->turboLen-1; i >= 1; i--) {
        turbo->body[i].dir = turbo->body[i-1].dir;
        tinygl_point_t current_pos = get_next_pos(turbo->body[i].pos, turbo->body[i].dir);
        turbo->body[i].pos = current_pos;
    }

    //update turbo pos and direction
    turbo->body[0].pos = current_head;
    turbo->body[0].dir = direction;
    for(uint8_t i = 0; i < turbo->turboLen; i++) {
        tinygl_draw_point (turbo->body[i].pos, 1);
    }

    //check if turbo ate the food
    if (turbo_eat_food(turbo)) {
        score++;
        create_food_task(turbo);
        grow_snake(turbo);
    }
}



void turbo_move_straight_task (void *data) 
{
    turbo_t* turbo = data;
    int direction = turbo->body[0].dir;
    if (get_gameState() == GAME_RUNNING) {
        if (direction == 0) {
            turbo_move(0, turbo);
        } 
        if (direction == 1) {
            turbo_move (1, turbo);
        }
        if (direction == 2) {
            turbo_move (2, turbo);
        }
        if (direction == 3) {
            turbo_move (3, turbo);
        }
    }   
} 













// static void run_turbo(turbo_t turbo)
// {

// }
    
    // if (game_state == GAME_RUNNING && ate_food ())
    // {
    //     char buffer[6];
        
    //     game_state = GAME_WAIT;
    //     led_set (LED1, 0);
    //     sprintf (buffer, "%d", duration);
    //     tinygl_text (buffer);
    // }


