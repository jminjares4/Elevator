idf_component_register(SRCS "src/led.c"
                            "src/pressure_sensor.c"
                            "src/accelerometer.c"
                            "src/servo.c"
                            "src/button.c"
                            "src/serial_communication.c"
                         #   "src/elevator.c"
                            "src/HAL_driver.c"
                            "main.c"
                        INCLUDE_DIRS ".")