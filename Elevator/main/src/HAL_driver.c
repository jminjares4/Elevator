#include "inc/accelerometer.h"
#include "inc/elevator.h"
#include "inc/led.h"
#include "inc/pressure_sensor.h"
#include "inc/serial_communication.h"
#include "inc/servo.h"
#include "inc/button.h"

//
void elevatorButtonInterrupt(void *arg);

/* ADXL335 setup */
Accelerometer acc = {
    .width = ACC_ADC_WIDTH,
    .xaxis = X_AXIS,
    .yaxis = Y_AXIS,
    .zaxis = Z_AXIS,
    .atten = ACC_ADC_ATTEN,
};

/* Elevator floor led setup */
Led floorLed[] = {
    {
        .gpio = 25,
        .state = LED_OFF,
    },
    {
        .gpio = 26,
        .state = LED_OFF,
    },
    {
        .gpio = 27,
        .state = LED_OFF
    },
};

int floorLedSize = 3; // sizeof(floorLed)/sizeof(Led);

/* Emergency setup */
Led emergencyLed = {
    .gpio = 23,
    .state = LED_OFF,
};

/* Arrow Led setup */
Led arrow[] = {
    {
        .gpio = 13, // up
        .state = LED_OFF,
    },
    {
        .gpio = 12, // down
        .state = LED_OFF,
    },
};
int arrowSize = 2; // sizeof(arrow)/sizeof(Led);

/* Elevator Button setup */
Button elevatorButton[] = {
    {
        .gpio = 15,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 2,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 4,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
};

int elevatorButtonSize = 3; // sizeof(elevatorButton)/sizeof(Button);

/* Emergency button setup */
Button emergencyButton = {
    .gpio = 5,
    .pull_sel.up = PULL_SEL_EN,
    .func = &elevatorButtonInterrupt,
};

/* PIR sensor setup */
Button hc_sr501 = {
    .gpio = 39,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = NULL,
};

/* Elevator setup */
Elevator myElevator = {
    .currFloor = 1,
    .destination = 1,
    .door = CLOSE,
    .state = IDLE,
    .prevState = IDLE,
    .dir = NONE,
};

/* SG90 setup */
Servo SG90 = {
    .timerNum = SERVO_TIMER,
    .pwmUnit = SERVO_PWM_UNIT,
    .signal = SERVO_PWM_SIGNAL,
    .gpio = SERVO_GPIO,
    .angle = 0};

/* Dispatcher Buttons setup */
Button dispatcherCallButton[] = {
    {
        .gpio = 18,
        .pull_sel.down = PULL_SEL_EN,
        .func = NULL,
    },
    {
        .gpio = 19,
        .pull_sel.down = PULL_SEL_EN,
        .func = NULL,
    },
    {
        .gpio = 21,
        .pull_sel.down = PULL_SEL_EN,
        .func = NULL,
    },
};

int dispatcherCallButtonSize = 3; // sizeof(dispatcherCallButton)/sizeof(Button);
