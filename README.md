# Elevator Final Project
The project consists of an Elevator Controller Unit (ECU) for Microprocessor 2 final project. ECU microcontroller (MCU) was Espressif ESP32 running FreeRTOS. The firmware has a custom hardware application layer (HAL) to avoid using Espressif API with a more approachable interface. Here is the list of all the files.
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

## **Microcontroller**
![ESP32](https://img.shields.io/static/v1?label=&logo=espressif&message=ESP32&color=000000)

## **Software**
![](https://img.shields.io/badge/Code-C-informational?style=flat&logo=C&color=003B57)

## **Real-Time-Operating-System (RTOS)**
![FreeRTOS](https://img.shields.io/static/v1?label=&message=&color=&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFUAAAAgCAYAAABjGjQoAAAAAXNSR0IArs4c6QAAGKFJREFUaEOtWneQXeV1%2F93%2B6vai7SvtSrtIQhKIFUIFIRBgUWRjOiZUm3hM%2FojjJOMaZlImEzsxycTBGBtEtynCYGNbElWAhAoSqKFV2ZW2abV939tXbr%2BZc777dgWGDH%2Fk7Xz77r3vu%2B38Tvmdcz4pCIIAn%2FMJECDwA%2Fiej1yQwbg9jpyTgRQAsiRBlmRI%2FK1AoSHLkGXaViEFMiSAf5dA82g%2F%2FOM7SuK3QHzTIZoPif%2BLHXEAcuEJJfD8gOYEYqq4Iu%2BK%2FYAPissEcnifwv7MhQuXlHkenzgjhfAahfuL64vfxdOJ%2B4sbiw16h8JH%2BmyhBiBZ08jbGaStSXSOfIxjqaMw%2FRx83xe%2F018QwIcf3lIc44fkO%2FosePG2JFghhAIYBIIkKbxPr69AgkLbsgKJfxNAyJIqAON5QowyFMgyHVchyxoUSYJK1wgFKkkGn0f3pHMIeKEAMisASYWuzwpBZ9Jv4qr86KQ0iiyejc8rKAZv05NKUGUNhmrAkA2osi7eld7800IVQiEAfIzbY%2Bg6cxi1RfVIGMVwZR9%2BQAL0GCASqEci5WMkaBIv7QfwfbqSBy%2Bg4SII6BwfLu37Pjyay7958H0a4jq8z0PMobn8my%2FO522%2BB9054HsJcMV54PPoaVz4sid%2BCxVKKKB4P5rHH9J8OhoqqlBYnoCA1ZjEF8okVEYCQYWGmB7HrOQszC5qRU2iEXEtwUB8SqjhA%2Fg%2BLM%2FBu%2F1vIpefxJrZ61Csl7N%2BkJkIAQKu68KxHWiaBlVTGGF6YfEpaOaM0RTMQzy3uBa%2FUsF2zzKzGWMsaD%2FNpVcVViGO0r1IoOI4AUFCpwkzYBcEfxboBDgpQggsXVFsC7Bom0EnaArzEAJcAN13w7lkkDoUKYK2yjZURMo%2FQ6iEchCgPzuA3x55FhfWX4il1RdBk3X2H%2FRnmiaOHj2KDz%2F6iAXa3NSM0tIyNM9pRtYbwkT%2B9LRpkXnNmJ4CTTZgaEnEtGJocpTN0%2FMtZO1x%2BIHL7gCSGpoYWWXB%2FAp%2BS2ZtmDE30jKCJhQyW4krBE4%2Bm88X5iq877TnEy6KESVgBYx0rYLbLFy14LCn%2FX4B%2FHBuf64Hmw6%2FgrmlC3Bl89o%2FN38SnO3beP%2F0dnw0shtfab0Bjck5IpgEASzHxoEDB%2FDiCy9i%2F4EDaGpsRHlFOcrLynHLHTejc%2FI1dKd2iiDEPk0IlX0ZdBhSBHG9DDXJuWituABxvRTj%2BQHsH9iKrDvBflL4scJ5hXPJH2pQZRXlkUY0lS%2BCocQEyG4eaWsMKXMYOXsKjpsH4PK1NCWKuF6Mkmg1kkYFdFKO0DOHYpx2H45vwXRzcDybASb3JXy6Dl2JwlAMaEqE30eYjQhYpzJH8fDBx2GN6%2FjHdX8HyQ%2BmsRG%2BJAD70le7Xoah6riy4RoUR0rDCB1gfGICTz31FHbt2oVYLAbDiCCTmcKyjgtw1Y2X4p3ejRh1TnKQ0hBFRCmBFzhwfBNOYLNGUFBJqhW4sPEmtFctR%2Ff4XmzregYZf4xfOJBcSGzapGEUfoSO0X9d1tBeejGWNW%2BAIukYzfTi1MQhnMl2I2UPwfLy8HwbkkQCUaBKGqJqAiXRWjSULMLs0sVI6mXiuiwYF1knjaGpkxjKdGHSGkbenYIXWKFQ6RoxROUilBplaCnvQEWikQMpe%2BggwPHJg3jo0EZ0HRnH47f%2F14xQp1ELfByd%2BBhbev6AC2etxNLKDmiKzmZEc8bGxvDQQw%2FhmWefgSzLUFUNF1%2B8CvfeezfkyhS29z%2BBXJCFFmhoSpyPhXVrELgORvO9ODa2E%2BNmP3wpgOyr6Ji1AStm34TB1Al0j%2B%2BDhRxr2mD2GLL2GFMnyVdREa9FRE6y9qiSjrayVWipXIye1GEcGnoPw7mTsPwp9oUqWYMaYyUgDXaDPMHEWp7Qy9BevhqLatbxNs1JW2ewt28L%2BqcOIWtPwPJNeHAFZSN3FzIXgrdMq8Lq5rvQXLYYEgcxwagOjO7Cw4cfR19nDk%2Fc8d%2Bh%2BQfgFyUf7%2Fh5vNfzJk5NncCVzdeirrhJ%2BDfmkgEs20ZnZye2bNmC0ZERzJs7DytWrkBNUwV29W1C5%2BTbHOGTcimW19%2BMhbWrSWkxmu%2FHjt4XcSq1j4NIJIhjbfOtWFBzOVzfhu3ZHMEHUsewq%2F%2B3GDG7EcgOjKAU6%2BbegcpYi3hRBFAlA4PZE%2Fjg9KsYzvfADRxovoaaxDy0VS9HRayetWg8P4RjI9vRn%2F4YnkSa7yMhl2HV7Jsxr3w5S2Rn78vYP7wVdpCDHEjQpQiKo7VIGlUcR%2FzAhulmkTUnYUhFuLT9blREG1ioBf66%2B8zbePjQk8j1RPHz2%2F7tk0Iloj%2BSO40%2F9fwepUY5Lq2%2FHAkjKYIHAM%2Fz0NvXh82bN6O7uxtLlizBooUL0dBQj7wygjeOb8SQfZIRLtUrsazpOlTF5sH2pnBq4gAOj%2B5Ayh6BFqiYXbQQl8y5A0WxWuaoZAV%2B4KBzaDve7X0eGXeUXUBVrA1XtX0TpZFaYS2Bj9HsKbzfQwB9CEey2Uk0xs%2FHssYvoyrewpYVSAFcz0Hv5AHs6HkRo1YvBy9yCe1lK7Fq9i3wvACbDv8rUu5ASK8UzC5ahI769Sg1aiHJ5HoAL7CRc9JwHRvVxS3Q5ch0kkIM4d2%2BLfjF4WcRHavFv3%2F1h58MVJ7v4aORfdjRvw0r6ldjUeV5glxDZqrS09uDf3jgAXR1daGsrAznLTkP%2BXwOt9xyI1A1hg8GNiHnpRHIPhPquFLO5urAgulnQNePy0k0lyzCuXVrURWdC1kRkZl8k%2Bmm8UH%2Fq%2Fhg8I%2Fw4EAOFCyoWoPVzbcgqpawtdheDkeG3sX7vc8j66cYjhK1EiuabkJL%2BUXQFI0ZRYG2jecHsb33eZwY3wlfIt4qoTbahivm3sec%2BLkDD8CGCYnpnYTaeCuW1q5HbbIdESXJwU6SiXIR9AKUszMo0uTXTv0ejxzahDqrDf987bdnhEovlXVyeK13K0azp3F1y7WYFa8NMw0FjuPgiSefxIubXsT69etxtLMT0UgUmqrgjm%2FcipPOOzgxuZNR9WWiPREADrzAFMw1UFGiVmB5wzWYW7YahpIUJIdzUCHUkWwvdvQ8h67UHkDyofgxXDLnNsyvWsvRl15qyhrD9pO%2FweHxd%2BEReL6EecUXYGXzTSiNNQiWBCUk8z4mzWG83%2Fc8Okd3ENNkDa6JzsUVc7%2FJALx8%2BKcYdfogBT6zKzLpqFKGyths1BbNQV1xC0ojdQyqwoDR81KOJqzXDUy8fOJ5bDz4Ks7XluO7V9w3I1Qivb3pHmw5%2BSfUF9XhkobLEFVjImWDAsuy8NP%2FfBCPPvooSktKWcgtLXNwzz13oa1jFnb0%2FQYjZj8CyUS51oB5VWvgeCZ6JvZi3OylhBVSoKGj5hosrb0GESPBD0ePRy9Kpn9qfD%2FeOfVrTISmGleqcM0530JNcgEzBtK%2FsdxpbOn8HwyYRzn1VXwNHXXrsbT2Wua%2BdCwM6wzUaLYP7%2FY8g5OpfQUGhKbkIlzW%2BnUUaeU4MrodH%2FVtRsobhOU7AGVl7H8lyL4MzY%2BhLFmPedVLMa%2FsIiT1yrCWIQKV6WXw62NP45mDW3FlyXr81ZqvkVApj5DgeBb2Du3CntM7sK55PdrLF%2FIrcz4kSTh2%2FDjefOtN7N%2B%2FH1PpKdTU1uKKy9eh48IlODr%2BFj4c3IxMkIYcBFhcfjlWtt4Gz3dxcOhN7Op9GS4s9pHzylZjVePNKI5WTZsRvTwFyMND27C95znYwRQAFfWJhVjXejdKo3VhNudhONuLVw%2F%2FB8a901w8UQIDyxq%2FgvNmfQkRNR7OC3207%2BLk5D5s634KE%2FaZsAaiYHH1FVjecB0SajHswMaZ1FGcnPgAw7k%2BtoS8NwE7zJw4U5MDxFCEhRVr2W%2FH1KJpn5p1UniycyNeOLgNN9TdgHsvuqEgVGDSmsQbpzZjyprEl9uuR5lRwQ%2FIBRPfx8OP%2FAKbNm3Cgw8%2BiJKSEsRicSQTceS8Uew89Ry6JvfAklyofgxfav0G2qqWc75%2BYnwv3jyxEblggjWtsWgJ1jT%2FBSriTSJFZapGZj2O3X2v4MDwVgQcfGJYXHUZLqy%2FDjG9ZLrMNJLtwR%2BOPIgxp58DohzIOLd6PTrqr0VCrxD8MSwGpe0R7Dv9Kg6ceR0umT6AuFyMtXPuRGv5%2BVAVA%2FBlTjctP8sCHc8NYjjThf7McYzkT4ISAlFDA0r1GlzW8nU0Fp87TTFT1ggeP%2FIYfndgJ%2B5svQO3dlxNrkSUJrrTXdjc9SrayubiksZ1nE6Sz6PCyMjoCL73ve%2Fhtddfxy0334JZtTVoqKvHipXLkdcH8X7fcxjN97HvLNPqcd3Cb6MkUsPC6pk4gNdPPIaUO8xmVR1t4QeblWgVPpXS1MDFUOYk3jn5awxkDiOQPESlEqxqugnnVF4MTY1Mp5iT5hC2dT2O7tTe6TpDZbQFS%2BvWo7l0MQw1AfgOZ1dHR%2Ffg0MhbmLKHw2qEinmlF2J5000ojVQxFeNAHGhh2STgYGY5WfSlj2D3wG8xnOvh7IxSpLhWjDVNd%2BKcyhUIWBkkjOT6sPHIY9h68CPcv%2BA%2BbFiyDpLn%2BwGhsWNwOz48sxsb5m7AnGQbcnkTXV3dmDWrGsPDw%2FjxT36CgYEB9q0UsTsu6MBffvMeZI1e7B%2Fagpw3Bfge5pVfhItbboOuRFjLeyeP4M3jT2DC7QMkD2XqLKxrvQ91xQvCPN9j6tM1vgfbTj6LKXeU8%2FFyrQlrW%2B9EQ%2FH8aZ5MkrHcPI4MvYM9%2Fb%2FDpD%2FK2k%2BlvMpoE%2BqSbYjpZfC8HCZyA%2BjPHEXGHefargYDs%2BItuKB%2BAxqKF8KHg87B9xCoKspi9YhpSRhKlEt%2Bnu9wdrVr4BUM5XqYP5O2lujVWNdyHxqL5yOQFRbqwFQXfnXkMew4fBR%2Fc%2F79uHzBKkie5wcT9jhe7n4JWgB8dd6NiMoJ7N6zh6P97bffjsHBQaiKiurqatiOzdUpyvVb5s5B1h3GaK6XKVDg26hOzEN1sgVshUTAs2fw8Zl3kLZPc%2BqnB1GcV38VqpItIf91Ybk2jgy9hb2n%2F0jki8tyjclFuKj5BpRH60LfK9gsuSLSwoPD23Bs7H2k7TNs2vQrleNUOcJuR6SZLgfDiJxAXXI%2B5ldfjIbiBdDVCFvWlo8fQiaYQDJagYRahohcBFWSOaKPW2f4vWzP5KxKDQzMLb0Aa%2BZ8DXGtBJAVzv27Jz%2FGL49sxIdHevH9FX%2BNVfM6ILmOHRybOobfHX8JF9etxLKa1bAsG4%2F88lec41991dXYvWc3rr%2F%2BeixfvhzRaBSJeBwlxcXsGiyHbhpwyqrIYA1VVI2FShGUuKlJubRvMaWRfIkLKmzSIZl3fRcTuT6M5AdA2whslESqUJ2cC0ONh1X%2BMEXgspyLtD2OgXQneicOYnCqD3l3En6QF%2BULiYrVMiJKHOXRBtSXLEJDcTvKYrXQ5AhVeXFsZC%2Fe7noE2SDNgZi7FSBXIMqIBJQUEFemFJdAWYiOxi%2BhLtnOhSJR%2FfdxZPxD%2FLLzSXR2DuOfLv0uzm9aCClvZ4I3%2Bl7D8dGPceP8W1Ebb0A2Z%2BJnP3sIP3%2F4YTiOhWwmg%2FLychQVFXER5bJLL8O9996Lbdu2YfOWzTAMA9FYHLF4DHEeCSQSYsTjFNDC7UQc8ViC50UjEcRjMagqtV6Ip5Jnp8qQKOFxRV4mX0fBcqbLIiqpovNAnJhSyJyd4tJh3s3A9R0%2BlypYSaOEg1xELeIyIxF5EgZFkeF0N46OvoMzmT6k7VFYDp1rCYIfiG5DREuiMlqDhtIlaCpbjFKjkrkqlSYJPLrORyM78KvOZ9F7bAo%2FXv8A2mvmQJo0x4LH9%2F8cdcW1uLb1JuiSAY9y9bExfLB3L77%2Fg%2B9jfns7Wlpbkctk2fxWrlyJpUuX4umnn8brr7%2BOXD6HnGkin89zbcC2KY8nhCUolDGxFsu8zUNVoakqdE1DjDQ%2FkWDAipJFSBYlxXZREeIERjweghRnQAm0aDSGaCyKWDSGSCQCXTegqqIoLorY4t5cxw0L66LGJQh7EHYSXD%2FH3NQKTLYk4tWeZ0GSfE4MdDUBQ05AV5NQZWrPiKxLJCsSV992Dr6JRztfwOQpHz%2FZ8ADmVDRCOjB6MHih80nc3H4z2ssWMRnn8lsQIJ2ZwvbtO3BO%2Bzmor6cihXggEgx9SIhUsKZEwHGdaYGa%2BTymMhmk02mkJicxOZni8mAqlcLU1BT%2FlsvlkMvmOM3NW3lYpg3bMvmbgqHtUjbmC9NUwpqqQuCoUBQViqpA0zVoqg5d1xGLRZBMJpBMJlFcUoziomIUJZK8n0gKYOJkTQRENAJDj8CI6IgYURhRA4auQzd0KErYG%2BNeVFjkDjuPZDl0bxI6yYesYlvfZjza%2BRLkMwn8y4YfoLG0BtLbve8Gh4b24LZzb0UR8byQfJAZiOYewS%2BxzxSd0c%2F%2BzDQ8RXtjpt0oelkzn0C0YVwXruOyVlumBdtxYJFQLROmabHmZ3NZBiadTiGVnkJ6Ko10KoV0ekqAkTdh0rBMvg65KmrvWLYD1xGDikBsNWHjkKpLxF5UTYOmq9BVnQVq6AaMiMHWIIBICgtKCmBKikuwbNkyLJg%2Fn1NV%2BqOEaeupV%2FDY4VdQmWnEj676DuqKKiG907sz%2BHBsF9bOXo2YHINOnctCy1nSuTBC5ivL5MxFK5p7joWWM1f4CyIrbEw3cqdlebbQRR3y7PbGWUL%2FM9RmDhTaGeSCXM9lIGxLaDZZTWEQGJZpIpfPI5vJsnVkMhlkshlkpjIMDh3Pm%2BIcAoZZDQHheQw6D4fAd3ibfP%2BPfvgj3H3XXWEx30fey%2BMP3S%2FgiUN%2FRDsW4W%2FXfQvViXJInaPdwU93%2FwyOkkHC0JCgliuPKGJqHFElioiqI6JSOzaCiBJhPke1Rl0xuBJPgyrs5Ieo3UGRlAbREwaB2yqiPVxolQitF81mwRMK9f1CW1PgMWMbhe7%2BzGzRqAi7o4XDnzSSMBcqXCsM2mG32HM91nAa5MY4NuRyyGbpO8vf2WyWt8kC1lyyhl2h%2BATIOCm8dOJZPL1%2FK1YmLsb9l9yD8ngxpCkzF7x8dAte69mGSXscLvE7bjlT4VoUF2SJeKDQVo2bbipUWYGmqDAUqrSLEdEMFnpEJcEbiMoEhthm4dN8OcK0S1MJDB2aRH1zjUGiPjr7TL6HWJRB33zvsHknQOFOfijyUJNZ86dXOxTWOExbytmLHT7Hg32uY%2BN2e%2BhCCtchMFPWKJ4%2F%2FhR%2Bs%2B8tbKi9FneuuBUlsQQkz%2FGClJPF8fFTOD15mnN%2F0zORJypFjTDPhOtSQ8yF6dmwPBO2b4lvz4ITuMxF6U%2F0330Q2WPuSqSZBCTJUBVJRH2Oqip0%2BpY1RBQaAhRdEcOQdQbCoN9kAYQhU5lRF0CoBlsJgaEqAhBdKoCi8BwloIBW6KSStZClFFxJYeXK2etbPu3CPkvGn2ycj%2BbP4NmjT%2BClD97DnW2344aOLyNpRCH5vkcSYIFQ0ZbyYRKS63ssMCLjHgUWz%2BPMx3JJoBa3PyyPeKI4Zk4PE3nX5P4QAWN6lthnEBwGg44RlaFrc9eSgKCIykBQhJcgEQiKLCxDUbgVrpN2KwSIGIassgAJHAGEzgImQCL8TfNpO7QWBo3AigrXRfO5Q0rnEThixQu7r7PiBre6C1SqsPYmCDCY7cejBzfijQ%2F24TsX3Y8rFl%2FCrlIKAlrPUfBrhYJxuJKjEMNDuxJLLYQ%2FKTQKfSbBYgUJZTokKAoiHEho%2BCINdTyiXXSMBGojHwrYtvNC8I4Jk4ZrIeuYyBIoXp6DEVmI6ZsMJrWPqadF9yr0nQgMAoFcBLkQKAE0RWbBCxclh%2FtkHQZURWYLIhB0BkYcZytRCKACKDPuK8JARBkAijmyZKB7cgBPvr8JSkrD3195P%2BY3tnLd93PWUn0RrzMTz8PmxSdOmqFR4ZKEkGZNgxG6Cqq5Cs4nlv%2FQihDHJ%2BE7DASDQxy4oOFsEeSexMjRcPM8iO%2Fm7Dwybm7GMnwClMAgwD34EuVtDlsF0ytiNeQmZIjERJZCoQsgyFIIGJ1oGGuyBikwYJkqRgbTkFIBvtZxHa5ctAaJKHVxP2Mt1RcR5xeZUxAqO%2FZClA4L3mefL%2BYJUQuXJ9Y2FVbDzCzrCRfNhUUVqiOI9VZUZCms2aKKF7kuAkJ0aGn5Ut7JC3fEYOSRtXLcOqLvKSuDjJ1DxsoiawvXRItJyN05gQeb3KEUptC8mkZCPudBtgwsKm3DzUuvwurWpSiOJpgL8xv8X0spv4jw%2Fn%2FmnJ0cfJobzewTJ5lht%2BE5IXkVS0JCgMJNETjFE4pFdMJ1FRbRcQGeC9oCFBIixQhhBTnknDxyVhaWayJjZZA2s5hyTCiyjtllDVg0qw2z4lUcfAVvF5%2F%2FBVbXRZf12xL6AAAAAElFTkSuQmCC)

## **Software Enviroment**
![Visual Studio Code](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=flat&logo=visual%20studio%20code&logoColor=white)

## **Electronic Design Automation**
![EasyEDA](https://img.shields.io/static/v1?label=&message=EasyEDA&color=5588FF&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGUAAABlCAYAAABUfC3PAAAAAXNSR0IArs4c6QAACJNJREFUeF7tnXlsF0UUx78th60iQoIQlSMmJh54RkKiiMFgjNFoIodQQChEDEEgBQGj4RASFSlHBZWjQKQCrQfRSMSLEDQQjRLBC1ACGkEBD1AwhdIi5tFOftPt7s6b3dnfb7bM%2Ftff782b976febP7252d5g2cc%2FYs3GGVAnkOilU8zgXjoNjHxEGxkImD4qDYqICFMblzioNioQIWhuQqxUGxUAELQ3KV4qBYqICFIblKcVAsVMDCkFylOCgWKmBhSKmvlJfHAB3a8pTd9DVQ%2FiHPNpdWqYTy%2BtT4klXXACNfjO8nCQ%2BpgmIChp%2BIg%2BYmIW10n6mAkhQMWbZj%2FwJjXokupMmWVkNp2QJY%2B4TJdNW%2BbKgaa6HMLQa6dVSLmIRFrsFYCaViInBBK77cNXXA8AXB9h3bAYsf4%2Fsjy1yCsQ5K2WjgsvY8AaMId1EBsGpCcv55nsOtsg6ldUvgtUnxQo8Cw9sjgacBoDpM9KXqw%2Ft9VqDk5wGVU3RDa2pPywYHl8b3I3vgXNllG0ziUDhJc2TesR%2BY8xbHUt9GFePTFcC%2Bw%2Fp%2Bo7ZIDIoqUZ2As%2FHrWxVvNqslESiqBHWAZPNKKCzuF9YDX%2B3TjTyavXEoaQVC8j1TBFzbJVzICcuBI39HE5vbyigUHSCTVwEH%2Fmwa5uyhwNVXZD7P5rRBvXJzGP0ScLyaK7OenTEonGRO1QIjFuoFmG1rTh5yTEkMmqxBSSL4pIDlGowRKKok0gREZwpLqmISh5I2ICR07%2B4A%2FeB9sCfQuQO%2FHk3lGhtKWJWc%2BQ8YMo%2BflM2Wg3sDD90WHuHG7cDqzfGzSBSKqZETP01zHrIxVTsoEXiFgTGxOCMxKFu%2BA5ZsjJBxCpq0KQRWjg8ONO4MkRiUofOBujN2Klw1BVj7CbDhi%2BjxhVWLtVDiBhZdruCWXiHjxJhKKDPWAT8cTEJafZ9JCHh9N2D6IP9Y4sAmj4lNX%2BQ8bnD68jduobpSIusRZcCp0%2Fo9tW8DLB17HkBRibjzJ%2BD5N9UCqvx4PUQZPA%2F0BIb1SSGU4jLgJGMU6oq45yAwc11TQXT9CA%2FDFwI1tWrYskUSU6LwH3v6Ui2EUI3CqEKK6bFFPrBusp6gwloVW5hXq6FQ4Cphg5JXtYsmtbpVHBjkvWoqkBfSTVz%2FsSuFYrvrRmDMveFieAPNBZC4YlGGbQuB8gR%2FOBq5%2BhIoOCKLcwzHVj3e%2BRYmYFBvnMfFJvoyUik6YDhSehMraAWsnshpmbGhneUGG3rF4c7uwOP3q%2Fs3AcRopZxzlgfQLYw4R1hinArTeeQ8bxTQReN5SVhe720HKgzctjcOhRwmeTUUBmX%2FYeCpCv5w4ADmezP7Q9no9CUnESVpVfkP7AUM6OUvlaqtt1WU%2BPx6%2FusEMHaJDj61bWJQqGvdxFXCrhgPXFxoDxR6qkpPV00fiULRvQDYdQCYVRmcoskfbLoDRo4q6WW0WYEiEurUDlikeHmHpgKaEnSnG1WV%2BaHWBTNsAVBbZ7oumvrLKhSdytm2G9i6C3iyv1qEYfOBWksfqKmjtwRKlPNNWHJRqiSKWNlqk5NKoeQWjgYuZ75Gdz4BoVxzBoU6p7e7aNFb1KO5VYjQIadQKIgbugHTAh6rnm8VYg0UEQjdnqHbNKqDdoWg3SGa85HzSvETt7gv0PcmgB6g%2FVMNjF%2Bm%2F2QwzdCshJJmQU3E7qCYUNGwDwfFsKAm3DkoJlQ07MNBMSyoCXcOigkVDfuIDEV1h7WkHDh0zHC0mu6WjwMuuTC8kXxXICgn7p0D0X7J%2B8CWbzWDlcwTg0J9cJOJHn54S9XAkWOc2g%2B49apgf5u%2FAZZ9EPw97cxEv6vEESf32FB%2BPgLUep6%2BVZ8CnmOs%2BU0KhvArQ6E45YNifvYN4GRN%2Faey7e4DwJWdgILWjduELcM1%2BZpFJCjXdAZmDakPWGdE3H0zsGknD8U9twAf7eDZBlnJQqniDLNV%2BfF7TK3qLyyzSFBWl2RGEadzv2lEZymrsBV%2BSlYAh442TstPOPHZ3t%2BAaWv4U503NtrLkva0DBqEOvlxhlkkKKqRI3ccNq%2FTOilaL%2BU33cg%2BxKt6nNFMq%2FFpVb48JY1bCvxxPDoU7%2FQmQ1s5AWhTkJkx%2BvcC1m%2FjSB9sExtKkGsKPEjEyslAfn6mpbcSxIgUW%2BCK7%2BXFfkFXTZyrKdGzny3tvOf3j3uDcqHPhR%2FajFT3lQo%2F%2FRKBcvQEsHV3%2FY4NnJIPguIXsBBHFk98Jr%2BVVdgaeLUkfMT6QeFMq8JG7ApLf6%2BZBLRqmQEkw9Ktm1hQKj8F3vncv0vVFBc28oTH6WuBH38NP3dw%2FKjOe%2FIelzpQRN%2FeNkGfc%2BHEghKWLBfK978As6uChafvyEYc%2FW8HHr6j%2Fi9aDCdeGAoSJqhS5R6n9AN6NPxGUUF5dDFw4mSmMrxTYekooGvD%2BmTaz4z2NdM9cg5FJYKfqJyrHdWgkIVS2YZd2akEV1WpkXMK9zdKWKIzi4DrGrYF9M7rnHme80NNJTQXiuznzFlgSGl9ddJCdjp%2B99m6kM4t9PYwp0qNQAm7xKUOTtcBjzRscS7binthQYLKn9NuQPf1yITrHW3ee1p%2Bo1EVp85VmneK4gCPc17Rnr5Uycqjg%2F6jA13Whh1%2BV16yvd%2F7JvJ5hTP9%2BfUvr5bXyUl%2B35FzTi17F%2Fhsj2qSa%2Fy9cSi03HTRhkwnQ%2FtkLo3p05UfZ26feC8bu14KlI7MtKX7UsU%2B%2Fw1IZ6QGycGplC%2F3AvPebuyB0ze14NoZmb70mJu3nlEEdPc5H5nvKXcetSsld6HW9yxGIO2QRLdfmuORKijl44C2DQ%2BtolxqpgVgqqCIKqFb%2BnRuaq5HqqA0VwjevBwUC0k7KA6KhQpYGJKrFAfFQgUsDMlVioNioQIWhuQqxUGxUAELQ3KV4qBYqICFIblKsRDK%2F0ANm%2Fr7waacAAAAAElFTkSuQmCC)

## **Author**
* [Jesus Minjares](https://github.com/jminjares4)
  * Master of Science in Computer Engineering

