/**
 * @file motion_sensor.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief motion_sensor.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/motion_sensor.h"


int motion_sensor_gpio_install_count = 0;

MotionSensor hc_sr501 = {
    .gpio = MOTION_SENSOR_GPIO,
    .pull_sel.down = PULL_SEL_EN,
    //.pull_sel.up = PULL_SEL_EN, // uncomment for pullup configuration
    .func = &motionSensorInterrupt,
};

/**
 * @brief motionSensorInit will intialize motion sensor for interrupt routine
 * 
 * @param sensor pass a MotionSensor by reference
 * @return None
 */
void motionSensorInit(MotionSensor *sensor)
{
    gpio_config_t ms_io_conf; // gpio_config_t to store configuration
    if (sensor->pull_sel.up)//check if pull-up is selected
    {
        ms_io_conf.intr_type = GPIO_INTR_NEGEDGE; // set as NEGEDGE for interrupt
        ms_io_conf.pull_down_en = 0;              // disable pull-down
        ms_io_conf.pull_up_en = 1;                // enable pull-up
    }
    else  //pulldown selected
    {
        ms_io_conf.intr_type = GPIO_INTR_POSEDGE; // set as NEGEDGE for interrupt
        ms_io_conf.pull_down_en = 1; // enable pull-down
        ms_io_conf.pull_up_en = 0;   // disable pull-up
    }
    ms_io_conf.mode = GPIO_MODE_INPUT;                // set input
    ms_io_conf.pin_bit_mask = (1ULL << sensor->gpio); // set gpio that will be used for input

    gpio_config(&ms_io_conf); //set configuration
    // if(motion_sensor_gpio_install_count++ == 0)
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3 | ESP_INTR_FLAG_IRAM); //set default flag for interrupts
    
    gpio_isr_handler_add(sensor->gpio, sensor->func, (void *)sensor->gpio); //pass the gpio number, routine and argument for the routine
}

#include "esp_intr_alloc.h"
