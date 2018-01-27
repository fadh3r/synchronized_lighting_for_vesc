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

#include "color_shifting.h"
#include "led_strip_apa102.h"
#include "color_palletes.h"


/* extern "C" - allows to use C header files with C++ code
   for more info see - https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c */
extern "C" {
  #include "vesc_uart.h"
};



void update_strip_colors(void) {
  uint32_t current_tacho_value;
  uint32_t pallete_travel;
  current_tacho_value = bldc_get_tachometer_value();
  pallete_travel = current_tacho_value / WHEEL_SIZE_RATIO;
  for (uint8_t i; i < LED_COUNT; i++) {
    led_strip_colors[i] = get_pallete_color(pallete_travel  + i);
  }
  update_strip();
}
