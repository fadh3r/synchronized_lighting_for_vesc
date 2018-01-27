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

#include "led_strip_apa102.h"

// Create an object for writing to LED strip.
APA102<DATA_PIN, CLOCK_PIN> led_strip;
// Create a buffer for holding colors (3 bytes per color).
rgb_color led_strip_colors[LED_COUNT];


void update_strip() {
    led_strip.write(led_strip_colors, LED_COUNT, LED_STRIP_BRIGHTNESS);
}
