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

void app_main(void)
{
  
}