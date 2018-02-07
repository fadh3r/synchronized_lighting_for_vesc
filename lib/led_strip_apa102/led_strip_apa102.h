/*
    This is Synchronized Lighting project for VESC controller
    Copyright (C) 2018  Maksim Reshetnikov ju_mpe_r@electric-skates.ru

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef LED_STRIP_APA102_H
#define LED_STRIP_APA102_H

    #include "stdint.h"
    #include <FastGPIO.h>
    #define APA102_USE_FAST_GPIO
    #include <APA102.h>

    /* define here Arduino pins connected to APA102 strip */
    #define DATA_PIN  11
    #define CLOCK_PIN  12
    /* define here number of leds on strip */
    #define LED_COUNT  42
    /* define APA102 brightness - 31 max */
    #define LED_STRIP_BRIGHTNESS 1

    extern rgb_color led_strip_colors[];

    void update_strip(void);

#endif /*  LED_STRIP_APA102_H */
