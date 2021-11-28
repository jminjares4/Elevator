#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "sdkconfig.h"
#include <string.h>
#include "esp_log.h"

#include "inc/accelerometer.h"
#include "inc/pressure_sensor.h"
#include "inc/led.h"
#include "inc/servo.h"
// #include "inc/motion_sensor.h"
#include "inc/button.h"
#include "inc/serial_communication.h"
extern Accelerometer acc;
extern PressureSensor pressSens;
// extern MotionSensor hc_sr501;
extern Servo SG90;
extern SerialComm externalSerial;
#define FLOOR_1 0
#define FLOOR_2 1
#define FLOOR_3 2

#define FLOOR_UP    0
#define FLOOR_DOWN  1

void elevatorButtonInterrupt(void * arg);
void motionSensorInterrupt(void *arg);
Led floorLed[] = {
    {
        .gpio = 13,
        .state = LED_OFF,
    },
    {
        .gpio = 12,
        .state = LED_OFF,
    },
    {.gpio = 14,
     .state = LED_OFF
    },
};

Led emergencyLed = {
    .gpio = 27,
    .state = LED_OFF,
};

Led arrow[] = {
    {
        .gpio = 15,
        .state = LED_OFF,
    },
    {
        .gpio = 2,
        .state = LED_OFF,
    },
};

Button elevatorButton[] = {
    {
        .gpio = 5,
        .pull_sel.up = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 18,
        .pull_sel.up = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 19,
        .pull_sel.up = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
};
Button emergencyButton = {
    .gpio = 21,
    .pull_sel.up = PULL_SEL_EN,
    .func = &elevatorButtonInterrupt,
};

#define MOTION_SENSOR_GPIO 21 //motion sensor gpio 
Button hc_sr501 = {
    .gpio = MOTION_SENSOR_GPIO,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = &motionSensorInterrupt,
};


void motionSensorInterrupt(void *arg){

}

void elevatorButtonInterrupt(void * arg){

}

void app_main(void)
{

    for(int i = 0; i < sizeof(floorLed)/sizeof(Led); i++){
        ledInit(&floorLed[i]);
    }
    ledInit(&emergencyLed);
    for(int i = 0; i < sizeof(arrow)/sizeof(Led); i++){
        ledInit(&arrow[i]);
    }

    buttonInitIRQ(&hc_sr501);


    for(int i =0; i < sizeof(elevatorButton)/sizeof(Button); i++){
        buttonInit(&elevatorButton[i]);
    }
    buttonInitIRQ(&emergencyButton);

    adcInit(&acc);
    pressureSensorInit(&pressSens);
    servoInit(&SG90);
    serialCommInit(&externalSerial);

    while(1){
        vTaskDelay(100/portTICK_PERIOD_MS);
    }

}