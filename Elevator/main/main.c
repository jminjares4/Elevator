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

#define FLOOR_UP 0
#define FLOOR_DOWN 1

bool MOTION_DETECTED = 0;
void elevatorButtonInterrupt(void *arg);
void motionSensorInterrupt(void *arg);
Led floorLed[] = {
    {
        .gpio = 14,
        .state = LED_OFF,
    },
    {
        .gpio = 27,
        .state = LED_OFF,
    },
    {.gpio = 26,
     .state = LED_OFF},
};

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

Button elevatorButton[] = {
    {
        .gpio = 4,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 2,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
    {
        .gpio = 15,
        .pull_sel.down = PULL_SEL_EN,
        .func = &elevatorButtonInterrupt,
    },
};
Button emergencyButton = {
    .gpio = 18,
    .pull_sel.down = PULL_SEL_EN,
    .func = &elevatorButtonInterrupt,
};

#define MOTION_SENSOR_GPIO 39 // motion sensor gpio
Button hc_sr501 = {
    .gpio = MOTION_SENSOR_GPIO,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = NULL,
};

QueueHandle_t myQueue;

typedef enum cartState_t
{
    IDLE = 0,
    MOVE = 1,
    STOP = 2,
    EMERGENCY = -1,
}cartState_t;

typedef enum direction_t
{
    DOWN = 0,
    UP = 1,
    NONE = -1,
}direction_t;
typedef enum door_t
{
    OPEN = 0,
    CLOSE = 1,
}door_t;

typedef struct Elevator
{
    uint8_t currFloor;
    uint8_t destination;
    door_t door;
    cartState_t state;
    cartState_t prevState;
    direction_t dir;
} Elevator;

Elevator myElevator = {
    .currFloor = 1,
    .destination = 1,
    .door = CLOSE,
    .state = IDLE,
    .prevState = IDLE,
    .dir = NONE,
};

#define X_AXIS_THRESH 1000
#define Y_AXIS_THRESH 2500
#define Z_AXIS_THRESH 2500

void task3(void *pvParameter)
{
    while (1)
    {
        switch (myElevator.state)
        {
        case IDLE:
            // waiting for queue
            if (xQueueReceive(myQueue, &myElevator.destination, 1000))
            {
                myElevator.door = CLOSE;
                myElevator.prevState = IDLE;
                myElevator.state = MOVE;
                if (myElevator.currFloor < myElevator.destination)
                {
                    myElevator.dir = UP;
                    ledOn(&arrow[FLOOR_UP]);
                    ledOff(&arrow[FLOOR_DOWN]);
                    // ledOff(&floorLed[myElevator.currFloor - 1]);
                }
                else if (myElevator.currFloor > myElevator.destination)
                {
                    myElevator.dir = DOWN;
                    ledOff(&arrow[FLOOR_UP]);
                    ledOn(&arrow[FLOOR_DOWN]);
                }
                else
                {
                    myElevator.door = OPEN;
                    myElevator.state = IDLE;
                    ledAllOff(arrow, 2);
                    moveServo(&SG90, SERVO_OPEN);
                    vTaskDelay(500 / portTICK_PERIOD_MS);

                    for (int i = -90; i < SERVO_MAX_DEGREE; i++)
                    {
                        if (buttonRead(&hc_sr501) == 1)
                        {
                            i = -90;
                            moveServo(&SG90, SERVO_OPEN); // open the doors
                        }
                        else
                        {
                            moveServo(&SG90, i);
                            vTaskDelay(20 / portTICK_PERIOD_MS);
                        }
                        vTaskDelay(10 / portTICK_RATE_MS);
                    }
                    myElevator.door = CLOSE;
                }
            }
            break;
        case MOVE:
            vTaskDelay(3000 / portTICK_RATE_MS);
            switch (myElevator.dir)
            {
            case UP:
                if (myElevator.currFloor == myElevator.destination)
                {
                    myElevator.prevState = MOVE;
                    myElevator.state = STOP;
                }
                else
                {
                    myElevator.currFloor++;
                    ledAllOff(floorLed, sizeof(floorLed) / sizeof(Led));
                    ledOn(&floorLed[myElevator.currFloor - 1]);
                }
                break;
            case DOWN:
                if (myElevator.currFloor == myElevator.destination)
                {
                    myElevator.prevState = MOVE;
                    myElevator.state = STOP;
                }
                else
                {
                    myElevator.currFloor--;
                    ledAllOff(floorLed, sizeof(floorLed) / sizeof(Led));
                    ledOn(&floorLed[myElevator.currFloor - 1]);
                }
                break;
            case NONE:
                break;
            }
            break;
        case STOP:
            ledAllOff(arrow, 2);
            ledOn(&floorLed[myElevator.currFloor - 1]);
            moveServo(&SG90, SERVO_OPEN);
            myElevator.prevState = STOP;
            myElevator.state = IDLE;
            myElevator.dir = NONE;

            for (int i = -90; i < SERVO_MAX_DEGREE; i++)
            {
                if (buttonRead(&hc_sr501) == 1)
                {
                    i = -90;
                    moveServo(&SG90, SERVO_OPEN); // open the doors
                }
                else
                {
                    moveServo(&SG90, i);
                    vTaskDelay(20 / portTICK_PERIOD_MS);
                }
                vTaskDelay(10 / portTICK_RATE_MS);
            }

            myElevator.door = CLOSE;
            break;
        case EMERGENCY:
            myElevator.prevState = EMERGENCY;
            ledOn(&emergencyLed);
            printf("911\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS); // should send 911 via uart
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void elevatorButtonInterrupt(void *arg)
{
    uint32_t gpio = (uint32_t)arg;
    uint8_t gpio_floor = 0;
    if (elevatorButton[FLOOR_1].gpio == gpio)
    {
        gpio_floor = 1;
        // ledOn(&floorLed[FLOOR_1_LED]);
    }
    else if (elevatorButton[FLOOR_2].gpio == gpio)
    {
        gpio_floor = 2;
        // ledOn(&floorLed[FLOOR_2_LED]);
    }
    else if (elevatorButton[FLOOR_3].gpio == gpio)
    {
        gpio_floor = 3;
        // ledOn(&floorLed[FLOOR_3_LED]);
    }
    else if (emergencyButton.gpio == gpio)
    {
        myElevator.state = EMERGENCY;
        // ledOff(&emergencyLed);
    }
    xQueueSendFromISR(myQueue, &gpio_floor, 0);
}

void task4(void *pvParameter)
{
    int x_axis = 0;
    int y_axis = 0;
    int z_axis = 0;
    int p = 0;
    while (1)
    {
        x_axis = read_axis(&acc, 0);
        y_axis = read_axis(&acc, 1);
        z_axis = read_axis(&acc, 2);

        p = read_pressure_sensor(&pressSens);

        printf("x: %d\ty: %d\tz:%d\tp: %d\n", x_axis, y_axis, z_axis, p);
        if (x_axis > 1950 || x_axis < 1750 || y_axis > 1950 || y_axis < 1750 || z_axis > Z_AXIS_THRESH || p > PRESSURE_SENSOR_THRESHOLD)
        {
            // myElevator.prevState = IDLE;
            myElevator.state = EMERGENCY;
            ledOn(&emergencyLed);
        }
        // else
        // {
        //     ledOff(&emergencyLed);
        // }
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

void task5(void *pvParameter)
{
    int x = 0;
    int y = 0;
    int z = 0;
    int p = 0;
    while (1)
    {
        x = read_axis(&acc, 0);
        y = read_axis(&acc, 1);
        z = read_axis(&acc, 2);
        p = read_pressure_sensor(&pressSens);
        char buffer[256];
        sprintf(buffer, "Pressure Sensor: %d\r\nX_AXIS: %d\r\nY_AXIS: %d\r\nZ_AXIS: %d\r\n", p,x, y, z);
        serial_write(&externalSerial, buffer, 256);
        memset(buffer, 0, sizeof(buffer));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{

    for (int i = 0; i < sizeof(floorLed) / sizeof(Led); i++)
    {
        ledInit(&floorLed[i]);
    }
    ledInit(&emergencyLed);
    for (int i = 0; i < sizeof(arrow) / sizeof(Led); i++)
    {
        ledInit(&arrow[i]);
    }

    buttonInit(&hc_sr501);

    for (int i = 0; i < sizeof(elevatorButton) / sizeof(Button); i++)
    {
        buttonInitIRQ(&elevatorButton[i]);
    }
    buttonInitIRQ(&emergencyButton);

    adcInit(&acc);
    pressureSensorInit(&pressSens);
    servoInit(&SG90);
    serialCommInit(&externalSerial);

    ledOn(&floorLed[FLOOR_1]);
    myQueue = xQueueCreate(3, sizeof(uint8_t));

    // xTaskCreate(&task, "task", 2048, NULL, 4, NULL);
    xTaskCreate(&task3, "task 3", 2048, NULL, 4, NULL);
    xTaskCreate(&task4, "task 4", 2048, NULL, 5, NULL);
    xTaskCreate(&task5, "task 5", 2048, NULL, 6, NULL);
}