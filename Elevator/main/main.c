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
#include "inc/motion_sensor.h"
#include "inc/button.h"

extern Accelerometer acc;
extern PressureSensor pressSens;
extern Led onboard;
extern Servo SG90;
extern MotionSensor hc_sr501;


void task5(void *arg)
{
    // const uart_port_t uart_num = UART_NUM_2;
    while (1)
    {
        // Write data to UART.
        char *test_str = "Jesus Minjares External UART API!\r\n";
        // uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
        serial_write(&externalSerial,test_str,strlen(test_str));
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    serialCommInit(&externalSerial);

    xTaskCreate(&task5, "task 5", 2048, NULL, 5, NULL);
}