# Synchronized Lighting for VESC

* The idea is to lightup the underbody of a skateboard in accordance with the movement - for example, like you skating the rainbow ;)

* You can choose from existing options and and also create your own lighting color palletes.

* While standby - "breathing lights" mode enabed.


## This project is easy to repeat - all you need is:

* [Arduino Nano](https://aliexpress.com/item/Nano-V3-ATmega328-CH340G-Micro-USB-Pin-headers-NOT-soldered-Compatible-for-Arduino-Nano-V3-0/32664577152.html) - brains for project

* [APA102](https://aliexpress.com/item/1m-5m-APA102-Smart-LED-Pixel-Strip-30-60-144-LEDs-Pixels-m-IP30-IP65-IP67/32780224340.html) - led strip

* [LM2596HVS](https://aliexpress.com/item/DC-DC-Converter-Adjustable-Power-Supply-DC-DC-Step-Down-3A-LM2596HVS-LM2596HV-DC-Step-Down/32485142548.html)) -  DC-DC step down converter


## Tuning your VESC Synchronized Lighting

1. Set strip length(led num) and strip brightness(1-31 max) in "lib/led_strip_apa102/led_strip_apa102.h" file:
```#define LED_COUNT  42
#define LED_STRIP_BRIGHTNESS  1
```

2. Tune "WHEEL_SIZE_RATIO" constant in "main.cpp" for velocity of color pallete change
```
const uint8_t WHEEL_SIZE_RATIO = 20;
```

3. Tune "STANDBY_TIMEOUT" constant in order to enable standby lighting mode
```
const uint16_t STANDBY_TIMEOUT = 3000;
```

4. Select "PPM and UART" in "APP setting" of "VESC tool".

5. You are ready to go!

6. You can create your own color palletes and set it up in "lib/color_palletes/color_palletes.h" file.

## If you use this project and like it - Please Donate
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](LHTUV26X68QS6)
