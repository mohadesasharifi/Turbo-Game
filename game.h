#ifndef GAME_H
#define GAME_H
#include <stddef.h>
#include "system.h"
#include "task.h"
#include "tinygl.h"

#define ROWS_NUM 7
#define COLS_NUM 5

#define DISPLAY_TASK_RATE 200

#define NAVSWITCH_TASK_RATE 50

#define TURBO_FLASH_TASK_RATE 5

#define TURBO_SPEED 2


enum dir {N=0, E=1, S=2, W=3};
typedef enum dir dir;

typedef struct bulb_s bulb_t;
struct bulb_s{
    tinygl_point_t pos;
    enum dir dir;
};


typedef struct turbo_s turbo_t;
struct turbo_s{
    uint8_t turboLen;
    bool alive;
    bulb_t body [35];
};

#endif