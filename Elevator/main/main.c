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
#define FLOOR_1_LED 0
#define FLOOR_2_LED 1
#define FLOOR_3_LED 2

#define FLOOR_1 0
#define FLOOR_2 1
#define FLOOR_3 2


#define FLOOR_UP    0
#define FLOOR_DOWN  1


bool MOTION_DETECTED = 0;
void elevatorButtonInterrupt(void * arg);
void motionSensorInterrupt(void *arg);
Led floorLed[] = {
    {
        .gpio = 26,
        .state = LED_OFF,
    },
    {
        .gpio = 27,
        .state = LED_OFF,
    },
    {.gpio = 14,
     .state = LED_OFF
    },
};

Led emergencyLed = {
    .gpio = 23,
    .state = LED_OFF,
};

Led arrow[] = {
    {
        .gpio = 13,
        .state = LED_OFF,
    },
    {
        .gpio = 12,
        .state = LED_OFF,
    },
};

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
Button emergencyButton = {
    .gpio = 5,
    .pull_sel.down = PULL_SEL_EN,
    .func = &elevatorButtonInterrupt,
};

#define MOTION_SENSOR_GPIO 39 //motion sensor gpio 
Button hc_sr501 = {
    .gpio = MOTION_SENSOR_GPIO,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = &motionSensorInterrupt,
};

void motionSensorInterrupt(void *arg){
    ledOn(&emergencyLed);
    MOTION_DETECTED = 1;
}

void elevatorButtonInterrupt(void * arg){
    uint32_t gpio = (uint32_t)arg;

    if(elevatorButton[FLOOR_1].gpio == gpio){
        ledOn(&floorLed[FLOOR_1_LED]);
    }else if(elevatorButton[FLOOR_2].gpio == gpio){
        ledOn(&floorLed[FLOOR_2_LED]);
    }else if(elevatorButton[FLOOR_3].gpio == gpio){
        ledOn(&floorLed[FLOOR_3_LED]);
    }else if(emergencyButton.gpio == gpio){
        ledOff(&emergencyLed);
    }
}

void task(void *pvParameter){
  while(1){
       
        for(int i =0; i < 2; i++){
            ledOn(&arrow[FLOOR_UP]);
            ledOn(&arrow[FLOOR_DOWN]);
            vTaskDelay(100/portTICK_PERIOD_MS);
            ledOff(&arrow[FLOOR_UP]);
            ledOff(&arrow[FLOOR_DOWN]);
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
    
        int read_pressure = read_pressure_sensor(&pressSens);
        int x_axis = read_axis(&acc, 0);
        int y_axis = read_axis(&acc, 1);
        int z_axis = read_axis(&acc, 2);

        printf("Pressure sensor: %d\n", read_pressure);
        printf("x-axis: %d\ty-axis: %d\tz-axis: %d\n", x_axis, y_axis, z_axis);

        vTaskDelay(100/portTICK_PERIOD_MS);


        if(MOTION_DETECTED){
            moveServo(&SG90, 90);
            MOTION_DETECTED = 0;
        }else{
             moveServo(&SG90, -90);
        }
       
    }
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
        buttonInitIRQ(&elevatorButton[i]);
    }
    buttonInitIRQ(&emergencyButton);

    adcInit(&acc);
    pressureSensorInit(&pressSens);
    servoInit(&SG90);
    serialCommInit(&externalSerial);

  
    xTaskCreate(&task,"task", 2048,NULL,4, NULL);   
}