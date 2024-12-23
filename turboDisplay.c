
#include <stdlib.h>
#include "turboDisplay.h"
#include "tinygl.h"
#include "game.h"
#include "task.h"
#include "buttonControl.h"
void display_task (__unused__ void *data)
{
    tinygl_update ();
}

void turbo_toggle (turbo_t* turbo)
{
    if (turbo->alive) {
        tinygl_pixel_set (turbo->body[0].pos, ! tinygl_pixel_get (turbo->body[0].pos));
    }
}

void turbo_flash_task (void *data)
{
    /* Flash the monster.  */
    turbo_t* turbo = data;
    if (get_gameState() == GAME_RUNNING)
        turbo_toggle (turbo);
}






// static int8_t thing_find (tinygl_point_t pos)
// {
//     uint8_t i;

//     for (i = 0; i < THINGS_NUM; i++)
//     {
//         if (things[i].pos.x == pos.x
//             && things[i].pos.y == pos.y
//             && things[i].alive)
//             return i;
//     }
//     return -1;
// }
