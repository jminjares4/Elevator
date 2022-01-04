# Elevator Final Project
Create a elevator controller
```
├── main
├── inc
    ├── accelerometer.h
    ├── button.h
    ├── elevator.h
    ├── HAL_driver
    ├── led.h
    ├── pressure_sensor.h
    ├── serial_communication.h
    └── servo.h
├── src
    ├── accelerometer.c
    ├── button.c
    ├── HAL_driver.c
    ├── led.c
    ├── pressure_sensor.c
    ├── serial_communication.c
    └── servo.c
├── Doxyfile
```
## Components
---
* [ADXL335](https://www.adafruit.com/product/163)
* [Buttons](https://www.amazon.com/6x6x6mm-Momentary-Push-Button-Switch/dp/B01GN79QF8)
* [Leds](https://www.amazon.com/Assorted-Lighting-Electronics-Components-Emitting/dp/B01CUGAFEC/ref=sr_1_4?keywords=LED%2Bsmd%2B0608&qid=1638487354&s=industrial&sr=1-4&th=1)
* [HC-SR501 PIR sensor](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)
* [Pressure sensor](https://www.amazon.com/Adafruit-Round-Force-Sensitive-Resistor-FSR/dp/B00XW2MIRQ/ref=sr_1_3?crid=1OGXQK6UD8IA6&keywords=force+sensitive+resistor&qid=1638487910&s=electronics&sprefix=Force+%2Celectronics%2C203&sr=1-3)
* [External serial headers](https://www.amazon.com/DEPEPE-2-54mm-Headers-Arduino-Prototype/dp/B074HVBTZ4/ref=sr_1_15_sspa?keywords=external+header+pin&qid=1638487958&sr=8-15-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUE4VUdQU09GMktDWlYmZW5jcnlwdGVkSWQ9QTAyMDgxMjQyMlRYNU5ENUxWVk5BJmVuY3J5cHRlZEFkSWQ9QTAxMzc4ODA2MzVFREQ2TURXSVYmd2lkZ2V0TmFtZT1zcF9tdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl)
* [Servo SG90 motors](https://www.amazon.com/Micro-Servos-Helicopter-Airplane-Controls/dp/B07MLR1498/ref=sr_1_1_sspa?keywords=SG90&qid=1638487991&sr=8-1-spons&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzRjRJWkkzMDFVMU45JmVuY3J5cHRlZElkPUEwODg1OTc2M0lBNjZSVzNFNUpPOSZlbmNyeXB0ZWRBZElkPUEwNjU4NjQ2MlVBWjVRWlZaM1A5VCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU&th=1)

## Doxygen
![image](https://user-images.githubusercontent.com/60948298/144520203-1a12df03-c54e-4767-9a92-effcdff6a5b9.png)

## Note
Create custom hardware application layer for all the components for the elevator controller unit

## Author
* [Jesus Minjares](https://github.com/jminjares4)
  * Embedded Software Engineer


![ESP32](https://img.shields.io/static/v1?label=&logo=espressif&message=ESP32&color=000000)
![](https://img.shields.io/badge/Code-C-informational?style=flat&logo=C&color=003B57)
![EasyEDA](https://img.shields.io/static/v1?label=&message=EasyEDA&color=5588FF&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGUAAABlCAYAAABUfC3PAAAAAXNSR0IArs4c6QAACJNJREFUeF7tnXlsF0UUx78th60iQoIQlSMmJh54RkKiiMFgjNFoIodQQChEDEEgBQGj4RASFSlHBZWjQKQCrQfRSMSLEDQQjRLBC1ACGkEBD1AwhdIi5tFOftPt7s6b3dnfb7bM%2Ftff782b976febP7252d5g2cc%2FYs3GGVAnkOilU8zgXjoNjHxEGxkImD4qDYqICFMblzioNioQIWhuQqxUGxUAELQ3KV4qBYqICFIblKcVAsVMDCkFylOCgWKmBhSKmvlJfHAB3a8pTd9DVQ%2FiHPNpdWqYTy%2BtT4klXXACNfjO8nCQ%2BpgmIChp%2BIg%2BYmIW10n6mAkhQMWbZj%2FwJjXokupMmWVkNp2QJY%2B4TJdNW%2BbKgaa6HMLQa6dVSLmIRFrsFYCaViInBBK77cNXXA8AXB9h3bAYsf4%2Fsjy1yCsQ5K2WjgsvY8AaMId1EBsGpCcv55nsOtsg6ldUvgtUnxQo8Cw9sjgacBoDpM9KXqw%2Ft9VqDk5wGVU3RDa2pPywYHl8b3I3vgXNllG0ziUDhJc2TesR%2BY8xbHUt9GFePTFcC%2Bw%2Fp%2Bo7ZIDIoqUZ2As%2FHrWxVvNqslESiqBHWAZPNKKCzuF9YDX%2B3TjTyavXEoaQVC8j1TBFzbJVzICcuBI39HE5vbyigUHSCTVwEH%2Fmwa5uyhwNVXZD7P5rRBvXJzGP0ScLyaK7OenTEonGRO1QIjFuoFmG1rTh5yTEkMmqxBSSL4pIDlGowRKKok0gREZwpLqmISh5I2ICR07%2B4A%2FeB9sCfQuQO%2FHk3lGhtKWJWc%2BQ8YMo%2BflM2Wg3sDD90WHuHG7cDqzfGzSBSKqZETP01zHrIxVTsoEXiFgTGxOCMxKFu%2BA5ZsjJBxCpq0KQRWjg8ONO4MkRiUofOBujN2Klw1BVj7CbDhi%2BjxhVWLtVDiBhZdruCWXiHjxJhKKDPWAT8cTEJafZ9JCHh9N2D6IP9Y4sAmj4lNX%2BQ8bnD68jduobpSIusRZcCp0%2Fo9tW8DLB17HkBRibjzJ%2BD5N9UCqvx4PUQZPA%2F0BIb1SSGU4jLgJGMU6oq45yAwc11TQXT9CA%2FDFwI1tWrYskUSU6LwH3v6Ui2EUI3CqEKK6bFFPrBusp6gwloVW5hXq6FQ4Cphg5JXtYsmtbpVHBjkvWoqkBfSTVz%2FsSuFYrvrRmDMveFieAPNBZC4YlGGbQuB8gR%2FOBq5%2BhIoOCKLcwzHVj3e%2BRYmYFBvnMfFJvoyUik6YDhSehMraAWsnshpmbGhneUGG3rF4c7uwOP3q%2Fs3AcRopZxzlgfQLYw4R1hinArTeeQ8bxTQReN5SVhe720HKgzctjcOhRwmeTUUBmX%2FYeCpCv5w4ADmezP7Q9no9CUnESVpVfkP7AUM6OUvlaqtt1WU%2BPx6%2FusEMHaJDj61bWJQqGvdxFXCrhgPXFxoDxR6qkpPV00fiULRvQDYdQCYVRmcoskfbLoDRo4q6WW0WYEiEurUDlikeHmHpgKaEnSnG1WV%2BaHWBTNsAVBbZ7oumvrLKhSdytm2G9i6C3iyv1qEYfOBWksfqKmjtwRKlPNNWHJRqiSKWNlqk5NKoeQWjgYuZ75Gdz4BoVxzBoU6p7e7aNFb1KO5VYjQIadQKIgbugHTAh6rnm8VYg0UEQjdnqHbNKqDdoWg3SGa85HzSvETt7gv0PcmgB6g%2FVMNjF%2Bm%2F2QwzdCshJJmQU3E7qCYUNGwDwfFsKAm3DkoJlQ07MNBMSyoCXcOigkVDfuIDEV1h7WkHDh0zHC0mu6WjwMuuTC8kXxXICgn7p0D0X7J%2B8CWbzWDlcwTg0J9cJOJHn54S9XAkWOc2g%2B49apgf5u%2FAZZ9EPw97cxEv6vEESf32FB%2BPgLUep6%2BVZ8CnmOs%2BU0KhvArQ6E45YNifvYN4GRN%2Faey7e4DwJWdgILWjduELcM1%2BZpFJCjXdAZmDakPWGdE3H0zsGknD8U9twAf7eDZBlnJQqniDLNV%2BfF7TK3qLyyzSFBWl2RGEadzv2lEZymrsBV%2BSlYAh442TstPOPHZ3t%2BAaWv4U503NtrLkva0DBqEOvlxhlkkKKqRI3ccNq%2FTOilaL%2BU33cg%2BxKt6nNFMq%2FFpVb48JY1bCvxxPDoU7%2FQmQ1s5AWhTkJkx%2BvcC1m%2FjSB9sExtKkGsKPEjEyslAfn6mpbcSxIgUW%2BCK7%2BXFfkFXTZyrKdGzny3tvOf3j3uDcqHPhR%2FajFT3lQo%2F%2FRKBcvQEsHV3%2FY4NnJIPguIXsBBHFk98Jr%2BVVdgaeLUkfMT6QeFMq8JG7ApLf6%2BZBLRqmQEkw9Ktm1hQKj8F3vncv0vVFBc28oTH6WuBH38NP3dw%2FKjOe%2FIelzpQRN%2FeNkGfc%2BHEghKWLBfK978As6uChafvyEYc%2FW8HHr6j%2Fi9aDCdeGAoSJqhS5R6n9AN6NPxGUUF5dDFw4mSmMrxTYekooGvD%2BmTaz4z2NdM9cg5FJYKfqJyrHdWgkIVS2YZd2akEV1WpkXMK9zdKWKIzi4DrGrYF9M7rnHme80NNJTQXiuznzFlgSGl9ddJCdjp%2B99m6kM4t9PYwp0qNQAm7xKUOTtcBjzRscS7binthQYLKn9NuQPf1yITrHW3ee1p%2Bo1EVp85VmneK4gCPc17Rnr5Uycqjg%2F6jA13Whh1%2BV16yvd%2F7JvJ5hTP9%2BfUvr5bXyUl%2B35FzTi17F%2Fhsj2qSa%2Fy9cSi03HTRhkwnQ%2FtkLo3p05UfZ26feC8bu14KlI7MtKX7UsU%2B%2Fw1IZ6QGycGplC%2F3AvPebuyB0ze14NoZmb70mJu3nlEEdPc5H5nvKXcetSsld6HW9yxGIO2QRLdfmuORKijl44C2DQ%2BtolxqpgVgqqCIKqFb%2BnRuaq5HqqA0VwjevBwUC0k7KA6KhQpYGJKrFAfFQgUsDMlVioNioQIWhuQqxUGxUAELQ3KV4qBYqICFIblKsRDK%2F0ANm%2Fr7waacAAAAAElFTkSuQmCC)