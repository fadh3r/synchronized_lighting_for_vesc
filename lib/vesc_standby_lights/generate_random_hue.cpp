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

#include <Arduino.h>
#include "generate_random_hue.h"

int16_t recent_random_color;

int16_t generate_random_hue(void) {
    int16_t random_hue;
    while(1) {
        random_hue = random(360);
        if (abs(recent_random_color - random_hue) > 60) {
            recent_random_color = random_hue;
            return random_hue;
        }
    }
}
