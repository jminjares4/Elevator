#include "inc/accelerometer.h"
#include "inc/elevator.h"
#include "inc/led.h"
#include "inc/pressure_sensor.h"
#include "inc/serial_communication.h"
#include "inc/servo.h"
#include "inc/button.h"

void elevatorButtonInterrupt(void *arg);

Led onboard = {
    .gpio = ONBOARD_LED,
    .state = LED_OFF,
};

/* ADXL335 Predefine structure */
Accelerometer acc = {
    .width = ACC_ADC_WIDTH,
    .xaxis = X_AXIS,
    .yaxis = Y_AXIS,
    .zaxis = Z_AXIS,
    .atten = ACC_ADC_ATTEN,
};

Led floorLed[] = {
    {
        .gpio = 25,
        .state = LED_OFF,
    },
    {
        .gpio = 26,
        .state = LED_OFF,
    },
    {.gpio = 27,
     .state = LED_OFF},
};

int floorLedSize = sizeof(floorLed)/sizeof(Led);


Led emergencyLed = {
    .gpio = 23,
    .state = LED_OFF,
};

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
int arrowSize = sizeof(arrow)/sizeof(Led);

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


int elevatorButtonSize = sizeof(elevatorButton)/sizeof(Button);

SerialComm dispatcher = {
    .gpio_rx = UART_0_RX,
    .gpio_tx = UART_0_TX,
    .gpio_rts = NO_PIN,
    .gpio_cts = NO_PIN,
    .uart_num = UART_0,
    .baud_rate = 115200,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = ONE_STOP_BIT,
    .data_bits = EIGHT_BITS,
};

Button emergencyButton = {
    .gpio = 5,
    .pull_sel.up = PULL_SEL_EN,
    .func = &elevatorButtonInterrupt,
};

Button hc_sr501 = {
    .gpio = 39,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = NULL,
};

Elevator myElevator = {
    .currFloor = 1,
    .destination = 1,
    .door = CLOSE,
    .state = IDLE,
    .prevState = IDLE,
    .dir = NONE,
};


Servo SG90 = {
    .timerNum = SERVO_TIMER,
    .pwmUnit = SERVO_PWM_UNIT,
    .signal = SERVO_PWM_SIGNAL,
    .gpio = SERVO_GPIO,
    .angle = 0
};

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