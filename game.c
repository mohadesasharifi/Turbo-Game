#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "turboDisplay.h"
#include "demo.h"
#include "game.h" 
#include "blueLed.h"
#include "buttonControl.h"
#include "task.h"
#include "turbo.h"

static void tasks (turbo_t* turbo) 
{   
    task_t tasks[] =
    {
        {.func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE, .data = turbo},
        {.func = turbo_move_straight_task, .period = TASK_RATE / TURBO_SPEED, .data = turbo},
        {.func = navswitch_task, .period = TASK_RATE / NAVSWITCH_TASK_RATE, .data = turbo},
        {.func = turbo_flash_task, .period = TASK_RATE / TURBO_FLASH_TASK_RATE, .data = turbo},
        
    };
    
    buttonControl_init ();
    bluLed_init ();
    demo_init ();
    // create_food_task(turbo);
    task_schedule (tasks, 4);

}

int main (void)
{
    turbo_t snake;
    bulb_t head;
    head.pos.x = 0;
    head.pos.y = 6;
    head.dir = 2;
    snake.body[0] = head;
    snake.turboLen = 1;
    snake.alive = 1;
    
    system_init();
    tasks (&snake);
    return 0;
}
