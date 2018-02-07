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

#include "color_palletes.h"
#include "led_strip_apa102.h"
#include "hsv_to_rgb.h"


rgb_color get_pallete_color(uint32_t position) {
   uint16_t hue;
   rgb_color rgb_return_val;
   if (position > 0)
      position = position % CURRENT_PALLETE_WIDTH;
   hue = pgm_read_word_near(CURRENT_PALLETE + position);
   rgb_return_val = hsvToRgb(hue, 255, 255);
   return rgb_return_val;
}
