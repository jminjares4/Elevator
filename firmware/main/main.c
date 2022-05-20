/*
    Author:     Jesus Minjares
                Master of Science in Computer Engineering
    Course:     EE 5190 Laboratory for Microprocessors Systems II                                      
                                         +-----------------------+
                                         | O      | USB |      O |
                                         |        -------        |
                                     3V3 | [ ]               [ ] | VIN
                                     GND | [ ]               [ ] | GND
     Touch3 / HSPI_CS0 / ADC2_3 / GPIO15 | [ ]               [ ] | GPIO13 / ADC2_4 / HSPI_ID / Touch4
 CS / Touch2 / HSPI_WP / ADC2_2 /  GPIO2 | [ ]               [ ] | GPIO12 / ADC2_5 / HSPI_Q / Touch5
      Touch0 / HSPI_HD / ADC2_0 /  GPIO4 | [ ]               [ ] | GPIO14 / ADC2_6 / HSPI_CLK / Touch6
                         U2_RXD / GPIO16 | [ ]               [ ] | GPIO27 / ADC2_7 / Touch7
                         U2_TXD / GPIO17 | [ ]               [ ] | GPIO26 / ADC2_9 / DAC2
                      V_SPI_CS0 /  GPIO5 | [ ]  ___________  [ ] | GPIO25 / ADC2_8 / DAC1
                SCK / V_SPI_CLK / GPIO18 | [ ] |           | [ ] | GPIO33 / ADC1_5 / Touch8 / XTAL32
        U0_CTS / MSIO / V_SPI_Q / GPIO19 | [ ] |           | [ ] | GPIO32 / ADC1_4 / Touch9 / XTAL32
                 SDA / V_SPI_HD / GPIO21 | [ ] |           | [ ] | GPIO35 / ADC1_7 
                  CLK2 / U0_RXD /  GPIO3 | [ ] |           | [ ] | GPIO34 / ADC1_6 
                  CLK3 / U0_TXD /  GPIO1 | [ ] |           | [ ] | GPIO39 / ADC1_3 / SensVN 
        SCL / U0_RTS / V_SPI_WP / GPIO22 | [ ] |           | [ ] | GPIO36 / ADC1_0 / SensVP 
                MOSI / V_SPI_WP / GPIO23 | [ ] |___________| [ ] | EN 
                                         |                       |
                                         |  |  |  ____  ____  |  |
                                         |  |  |  |  |  |  |  |  |
                                         |  |__|__|  |__|  |__|  |
                                         | O                   O |
                                         +-----------------------+
*/
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

//Call all variables 
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
extern int dispatcherCallButtonSize;


QueueHandle_t myQueue;
QueueHandle_t dispatcherQueue;
/**
 * @brief task1 will run the dispatcher that will send data to task 2
 * 
 * @param pvParameter arguments pass to the task 
 */
void task1(void *pvParameter)
{
    uint8_t num = 0; //temp variable
    while (1)
    {
        vTaskDelay(100/portTICK_RATE_MS); //debounce
        if(buttonRead(&dispatcherCallButton[CALL_BUTTON_0])){ //read button
            num = 1;
            xQueueSend(dispatcherQueue,(void *)&num, 0); //send 1
        }else if(buttonRead(&dispatcherCallButton[CALL_BUTTON_1])){ // read button 
            num = 2;
            xQueueSend(dispatcherQueue,(void *)&num, 0); //send 2
        }else if(buttonRead(&dispatcherCallButton[CALL_BUTTON_2])){
            num = 3;
            xQueueSend(dispatcherQueue,(void *)&num, 0); //send 3
        }else{
            vTaskDelay(100/portTICK_PERIOD_MS); //avoid WDT 
        }
        num = 0; //reset num
    }
}

/**
 * @brief task 2 will receive data from task 1 and update the elevator for the FSM to run
 * 
 * @param pvParameter arguments pass to the task 
 */
void task2(void *pvParameter){
    uint8_t data = 0; // temp data
    while(1){
        if(xQueueReceive(dispatcherQueue,&data, 100)){ //wait for data to be received 
            xQueueSendToBack(myQueue,(void*)&data, 100); //send data via myQueue
        }else{
            vTaskDelay(100/portTICK_PERIOD_MS); //avoid WDT
        }
    }
}

/**
 * @brief task 3 will run the FSM
 * 
 * @param pvParameter arguments pass to the task 
 */
void task3(void *pvParameter)
{
    while (1)
    {
        switch (myElevator.state) //check current state
        {
        case IDLE: //IDLE state
            // waiting for queue
            if (xQueueReceive(myQueue, &myElevator.destination, 1000))
            {
                myElevator.door = CLOSE; //close door
                myElevator.prevState = IDLE;  
                myElevator.state = MOVE; // update state
                if (myElevator.currFloor < myElevator.destination) //check if current floor is less than destination
                {
                    myElevator.dir = UP; // up direction 
                    ledOn(&arrow[FLOOR_UP]);
                    ledOff(&arrow[FLOOR_DOWN]);
                }
                else if (myElevator.currFloor > myElevator.destination) //check if current floor is greater less than desitnation
                {
                    myElevator.dir = DOWN; //down direction
                    ledOff(&arrow[FLOOR_UP]);
                    ledOn(&arrow[FLOOR_DOWN]);
                }
                else
                {
                    myElevator.door = OPEN; //open state
                    myElevator.state = IDLE; //update state
                    ledAllOff(arrow, 2);
                    moveServo(&SG90, SERVO_OPEN); //open servo
                    vTaskDelay(500 / portTICK_PERIOD_MS); //delay
                    for (int i = -90; i < SERVO_MAX_DEGREE; i++) //iterate -90 to 90
                    {
                        if (buttonRead(&hc_sr501) == 1) //check sensor 
                        {
                            i = -90; //reopen servo
                            moveServo(&SG90, SERVO_OPEN); // open the doors
                        }
                        else
                        {
                            moveServo(&SG90, i); //keep iterating 
                            vTaskDelay(20 / portTICK_PERIOD_MS);
                        }
                        vTaskDelay(10 / portTICK_RATE_MS);
                    }
                    myElevator.door = CLOSE; //close door 
                }
            }
            break;
        case MOVE: //MOVE state
            vTaskDelay(1000 / portTICK_RATE_MS);
            switch (myElevator.dir) //check the direction of the motor
            {
            case UP: // UP state of the door
                if (myElevator.currFloor == myElevator.destination) //check if the floor is at the destination
                {
                    myElevator.prevState = MOVE;
                    myElevator.state = STOP; //set to stop state 
                }
                else
                {
                    myElevator.currFloor++; //increment current flor 
                    ledAllOff(floorLed, floorLedSize); 
                    ledOn(&floorLed[myElevator.currFloor - 1]);
                }
                break;
            case DOWN: // DOWN state of the door 
                if (myElevator.currFloor == myElevator.destination) // check if the floor is at destination
                {
                    myElevator.prevState = MOVE; 
                    myElevator.state = STOP; // set to stop state
                }
                else
                {
                    myElevator.currFloor--; //decrement
                    ledAllOff(floorLed, floorLedSize);
                    ledOn(&floorLed[myElevator.currFloor - 1]);
                }
                break;
            case NONE:
                break;
            }
            break;
        case STOP: // STOP state 
            ledAllOff(arrow, 2);
            ledOn(&floorLed[myElevator.currFloor - 1]);
            moveServo(&SG90, SERVO_OPEN);
            myElevator.prevState = STOP;
            myElevator.state = IDLE; // update state 
            myElevator.dir = NONE; //set direction to none

            for (int i = -90; i < SERVO_MAX_DEGREE; i++) //iterate over -90 to 90
            {
                if (buttonRead(&hc_sr501) == 1) //check 
                {
                    i = -90;
                    moveServo(&SG90, SERVO_OPEN); // open the doors
                }
                else
                {
                    moveServo(&SG90, i); //move the servo 
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

/**
 * @brief elevatorButtonInterrupt interrupt routine that will update the elevator floor from the cart
 * 
 * @param arg arguments pass to the task 
 */
void elevatorButtonInterrupt(void *arg)
{
    uint32_t gpio = (uint32_t)arg; //capture argument
    uint8_t gpio_floor = 0;
    if (elevatorButton[FLOOR_1].gpio == gpio) //check for button 1
    {
        gpio_floor = 1;
        // ledOn(&floorLed[FLOOR_1_LED]);
    }
    else if (elevatorButton[FLOOR_2].gpio == gpio) //check for button 2
    {
        gpio_floor = 2;
        // ledOn(&floorLed[FLOOR_2_LED]);
    }
    else if (elevatorButton[FLOOR_3].gpio == gpio) //check for button 3
    {
        gpio_floor = 3;
        // ledOn(&floorLed[FLOOR_3_LED]);
    }
    else if (emergencyButton.gpio == gpio) //check for emergency
    {
        myElevator.state = EMERGENCY;
        // ledOff(&emergencyLed);
    }
    xQueueSendFromISR(myQueue, &gpio_floor, 0); //send queue data 
}

/**
 * @brief task4 read all the sensors of the elevator 
 * 
 * @param pvParameter arguments pass to the task 
 */
void task4(void *pvParameter)
{
    int x_axis = 0, y_axis = 0, z_axis = 0, p = 0; //temp variables
    while (1)
    {
        x_axis = read_axis(&acc, 0); // read x axis
        y_axis = read_axis(&acc, 1); // read y axis 
        z_axis = read_axis(&acc, 2); // read z axis

        p = read_pressure_sensor(&pressSens); // read pressure sensor 

        printf("x: %d\ty: %d\tz:%d\tp: %d\n", x_axis, y_axis, z_axis, p); // print data to the terminal to view for debugging 
        //check all threshold for the sensors 
        if (x_axis > 1950 || x_axis < 1750 || y_axis > 1950 || y_axis < 1750 || z_axis > Z_AXIS_THRESH || p < PRESSURE_SENSOR_THRESHOLD)
        {
            myElevator.state = EMERGENCY; //set state to emergency
        }
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

/**
 * @brief task5 debugging task will print data to UART 2 
 * 
 * @param pvParameter arguments pass to the task 
 */
void task5(void *pvParameter)
{
    //temp variables
    int x = 0, y = 0, z = 0, p = 0;
    char buffer[256];
    while (1)
    {
        x = read_axis(&acc, 0); // read x axis
        y = read_axis(&acc, 1); // read y axis 
        z = read_axis(&acc, 2); // read z axis 
        p = read_pressure_sensor(&pressSens); // read pressure sensor 
        
        sprintf(buffer, "Pressure Sensor: %d\r\nX_AXIS: %d\r\nY_AXIS: %d\r\nZ_AXIS: %d\r\n", p, x, y, z);
        serial_write(&externalSerial, buffer, sizeof(buffer)); //write to UART_x
        memset(buffer, 0, sizeof(buffer)); //clear buffer
        vTaskDelay(1000 / portTICK_PERIOD_MS); //1 second delay
    }
}

void app_main(void)
{

    //initiate all leds for the floor 
    for (int i = 0; i < floorLedSize; i++) ledInit(&floorLed[i]);
    // initiate emergency led 
    ledInit(&emergencyLed);

    // initiate all leds for the arrows
    for (int i = 0; i < arrowSize; i++) ledInit(&arrow[i]);
    
    //intiate the PIR sensor
    buttonInit(&hc_sr501);

    // initiate dispatcher buttons
    for( int i =0; i < dispatcherCallButtonSize; i++) buttonInit(&dispatcherCallButton[i]);
    
    //initiate elevator buttons 
    for (int i = 0; i < elevatorButtonSize; i++) buttonInitIRQ(&elevatorButton[i]);
    
    // initiate button interrupts
    buttonInitIRQ(&emergencyButton);

    //initiate acclerometer
    adcInit(&acc);
    //initiate pressure sensor
    pressureSensorInit(&pressSens);
    //initiate SG90 servo motor
    servoInit(&SG90);
    //intiiate UART 
    serialCommInit(&externalSerial);

    //set LED 1 on 
    ledOn(&floorLed[FLOOR_1]);

    //create queue to store uint8_t 
    myQueue = xQueueCreate(3, sizeof(uint8_t));

    //create queue to store uint8_t 
    dispatcherQueue = xQueueCreate(1, sizeof(uint8_t));

    //Create all task from task 1 being the highest priority to task 5
    xTaskCreate(&task1, "task 1", 2048, NULL, 7, NULL);
    xTaskCreate(&task2, "task 2", 2048, NULL, 6, NULL);
    xTaskCreate(&task3, "task 3", 2048, NULL, 5, NULL);
    xTaskCreate(&task4, "task 4", 2048, NULL, 4, NULL);
    xTaskCreate(&task5, "task 5", 2048, NULL, 3, NULL);
}