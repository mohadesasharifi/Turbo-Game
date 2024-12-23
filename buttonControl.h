#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H
#include "game.h"
typedef enum game_state
{
    GAME_WAIT,                  /* Waiting to start.  */
    GAME_RUNNING,               /* trubo running around.   */
    GAME_PAUSED                 /* turbo paused.  */
} game_state_t;

void buttonControl_init(void);
void game_state_init(turbo_t* turbo);
void navswitch_task (void *data);
game_state_t get_gameState(void);


#endif