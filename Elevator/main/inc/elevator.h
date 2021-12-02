#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "stdint.h"

/**
 * @struct Elevator elevator.h
 * @brief Elevator struct is a custom structure that will hold all the data for the elevator
 * 
 */


/**
 * @brief cartState_t elevator.h
 * 
 * This is a custom enumeration for the cart state cartState_t
 * 
 * 
 * ### Example
 * ~~~.c
 * 
 * typedef enum cartState_t{
 *  IDLE = 0,
 *  MOVE = 1,
 *  STOP = 2
 *  EMERGENCY = -1
 * }cartState_t;
 * 
 * ~~~
 * 
 */
typedef enum cartState_t
{
    IDLE = 0,
    MOVE = 1,
    STOP = 2,
    EMERGENCY = -1,
} cartState_t;


/**
 * @brief direction_t elevator.h
 * 
 * This is a custom enumeration for the direction state direction_t
 * 
 * ### Example
 * 
 * ~~~.c
 * typedef enum direction_t{
 *  DOWN = 0,
 *  UP = 1,
 *  NONE = -1,
 * }direction_t;
 * 
 * ~~~ 
 */
typedef enum direction_t
{
    DOWN = 0,
    UP = 1,
    NONE = -1,
} direction_t;


/**
 * @brief door_t elevator.h
 * 
 * This is a custom enumeration for the door state door_t
 * 
 * ### Example
 * 
 * ~~~.c
 * typedef enum door_t{
 *  OPEN = 0,
 *  CLOSE = 1,
 * }door_t;
 * ~~~ 
 */
typedef enum door_t
{
    OPEN = 0,
    CLOSE = 1,
} door_t;

/**
 * @brief Elevator elevator.h
 * 
 * This is a custom structure for the Elevator
 *  
 * ### Example
 * ~~~.c
 * typedef struct Elevator{
 *   uint8_t currFloor;
 *   uint8_t destination;
 *   door_t door;
 *   cartState_t state;
 *   cartState_t prevState;
 *   direction_t dir;
 * }Elevator;
 * ~~~ 
 */
typedef struct Elevator
{
    uint8_t currFloor; /*!< current floor */
    uint8_t destination; /*!< floor destination*/
    door_t door; /*!< door enum */
    cartState_t state; /*!< state of the cart */
    cartState_t prevState; /*!< previous state */
    direction_t dir; /*!< direction of the motors */
} Elevator;

#endif