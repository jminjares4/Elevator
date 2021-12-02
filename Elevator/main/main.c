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
#include "inc/elevator.h"
#include "inc/HAL_driver.h"

extern Accelerometer acc;
extern PressureSensor pressSens;
extern Servo SG90;
extern SerialComm externalSerial;
extern Led floorLed[];
extern Led emergencyLed;
extern Led arrow[];
extern Button elevatorButton[];
extern SerialComm dispatcher;
extern Button emergencyButton;
extern Button hc_sr501;
extern Elevator myElevator;
extern int floorLedSize;
extern int arrowSize;
extern int elevatorButtonSize;
extern Button dispatcherCallButton[];

SemaphoreHandle_t semaphore1; //, semaphore2;
// QueueHandle_t queue1;

QueueHandle_t myQueue;


int dispatcherCallButtonSize = sizeof(dispatcherCallButton)/sizeof(Button);


#define CALL_BUTTON_0 0
#define CALL_BUTTON_1 1
#define CALL_BUTTON_2 2

QueueHandle_t dispatcherQueue;

void task1(void *pvParameter)
{
    uint8_t num = 0;
    while (1)
    {
        vTaskDelay(100/portTICK_RATE_MS); //debounce
        if(buttonRead(&dispatcherCallButton[CALL_BUTTON_0])){
            num = 1;
            xQueueSend(dispatcherQueue,(void *)&num, 0);
        }else if(buttonRead(&dispatcherCallButton[CALL_BUTTON_1])){
            num = 2;
            xQueueSend(dispatcherQueue,(void *)&num, 0);
        }else if(buttonRead(&dispatcherCallButton[CALL_BUTTON_2])){
            num = 3;
            xQueueSend(dispatcherQueue,(void *)&num, 0);
        }else{
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        // printf("Num: %d\n", num);
        num = 0;
    }
}

void task2(void *pvParameter){
    uint8_t data = 0;
    while(1){
        if(xQueueReceive(dispatcherQueue,&data, 100)){
            myElevator.destination = data;
            myElevator.state = IDLE;
            //update elevator
            // xSemaphoreGive(semaphore1);
            xQueueSendToBack(myQueue,(void*)&myQueue, 100);
            // myQueue
            //send semaphore
        }else{
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
    }
}

void task3(void *pvParameter)
{
    while (1)
    {
        // if (xSemaphoreTake(semaphore1, pdMS_TO_TICKS(100)) == pdTRUE)
        // {
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
                    //    xSemaphoreGive(semaphore1);
                }
            }
            break;
        case MOVE:
            vTaskDelay(1000 / portTICK_RATE_MS);
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
                    ledAllOff(floorLed, floorLedSize);
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
                    ledAllOff(floorLed, floorLedSize);
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
            // printf("911\n");
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
        // if (xSemaphoreTake(semaphore2, pdMS_TO_TICKS(100)) == pdTRUE)
        // {
        x_axis = read_axis(&acc, 0);
        y_axis = read_axis(&acc, 1);
        z_axis = read_axis(&acc, 2);

        p = read_pressure_sensor(&pressSens);

        printf("x: %d\ty: %d\tz:%d\tp: %d\n", x_axis, y_axis, z_axis, p);
        // if (x_axis > 1950 || x_axis < 1750 || y_axis > 1950 || y_axis < 1750 || z_axis > Z_AXIS_THRESH || p > PRESSURE_SENSOR_THRESHOLD)
        // {
        //     // myElevator.prevState = IDLE;
        //     myElevator.state = EMERGENCY;
        //     ledOn(&emergencyLed);
        // }
        // else
        // {
        //     ledOff(&emergencyLed);
        // }
        vTaskDelay(500 / portTICK_RATE_MS);
        // xSemaphoreGive(semaphore2);
        // }
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
        sprintf(buffer, "Pressure Sensor: %d\r\nX_AXIS: %d\r\nY_AXIS: %d\r\nZ_AXIS: %d\r\n", p, x, y, z);
        serial_write(&externalSerial, buffer, 256);
        memset(buffer, 0, sizeof(buffer));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{

    for (int i = 0; i < floorLedSize; i++)
        ledInit(&floorLed[i]);

    ledInit(&emergencyLed);

    for (int i = 0; i < arrowSize; i++)
        ledInit(&arrow[i]);
    
    buttonInit(&hc_sr501);

    for( int i =0; i < dispatcherCallButtonSize; i++)
        buttonInit(&dispatcherCallButton[i]);
    
    for (int i = 0; i < elevatorButtonSize; i++)
        buttonInitIRQ(&elevatorButton[i]);
    
    buttonInitIRQ(&emergencyButton);

    adcInit(&acc);
    pressureSensorInit(&pressSens);
    servoInit(&SG90);
    serialCommInit(&externalSerial);

    ledOn(&floorLed[FLOOR_1]);
    myQueue = xQueueCreate(3, sizeof(uint8_t));

    // queue1 = xQueueCreate(3, sizeof(int));
    semaphore1 = xSemaphoreCreateBinary();
    // semaphore2 = xSemaphoreCreateBinary();

    serialCommInit(&dispatcher);

    dispatcherQueue = xQueueCreate(3, sizeof(uint8_t));

    xTaskCreate(&task1, "task 1", 2048, NULL, 7, NULL);
    xTaskCreate(&task2, "task 2", 2048, NULL, 6, NULL);
    xTaskCreate(&task3, "task 3", 2048, NULL, 5, NULL);
    xTaskCreate(&task4, "task 4", 2048, NULL, 4, NULL);
    xTaskCreate(&task5, "task 5", 2048, NULL, 3, NULL);
}