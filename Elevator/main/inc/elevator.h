#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "stdint.h"
typedef enum cartState_t
{
    IDLE = 0,
    MOVE = 1,
    STOP = 2,
    EMERGENCY = -1,
} cartState_t;

typedef enum direction_t
{
    DOWN = 0,
    UP = 1,
    NONE = -1,
} direction_t;
typedef enum door_t
{
    OPEN = 0,
    CLOSE = 1,
} door_t;

typedef struct Elevator
{
    uint8_t currFloor;
    uint8_t destination;
    door_t door;
    cartState_t state;
    cartState_t prevState;
    direction_t dir;
} Elevator;

#endif