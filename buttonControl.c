#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "navswitch.h"
#include "timer.h"
#include "buttonControl.h"
#include "task.h"
#include "turbo.h"
#include "blueLed.h"
#include "turboFood.h"

// static int duration = 0;
static game_state_t game_state = GAME_WAIT;

game_state_t get_gameState(void) 
{
    return game_state;
}

void buttonControl_init (void)
{
    navswitch_init ();
}

void navswitch_task (void *data)
{
    
    turbo_t* turbo = data;

    navswitch_update ();

    if (navswitch_push_event_p (NAVSWITCH_NORTH))
        turbo_move (0, turbo);
    if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        turbo_move (2, turbo);
    if (navswitch_push_event_p (NAVSWITCH_EAST))
        turbo_move (1, turbo);
    if (navswitch_push_event_p (NAVSWITCH_WEST))
        turbo_move (3, turbo);
    
    /* Pause/resume turbo running around.  */
    if (navswitch_push_event_p (NAVSWITCH_PUSH))
    {
        switch (game_state)
        {
        case GAME_WAIT:
            // create_food_task(turbo);
            game_state = GAME_RUNNING;
            srand (timer_get ());
            tinygl_clear ();
            create_food_task(turbo);
            turn_on_blue_led();
            break;
            
        case GAME_RUNNING:
            game_state = GAME_PAUSED;
            turn_off_blue_led();
            break;

        case GAME_PAUSED:
            game_state = GAME_RUNNING;
            turn_on_blue_led();
            break;
        }
    }
}
