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

#include <stdint.h>
#include "breathing_lights.h"
#include "led_strip_apa102.h"
#include "generate_random_hue.h"
#include "hsv_to_rgb.h"
#include "cie1931.h"

extern "C" {
  #include "vesc_uart.h"
};

uint32_t previous_tacho_value = 0;
uint32_t previous_millis = 0;
uint8_t fadeout_flag = 0;
uint8_t standby_flag = 0;


static bool vesc_standby_tacho(void) {
  bldc_get_values();
  if (previous_tacho_value == bldc_get_tachometer_value()) return true;
  return false;
}

static bool vesc_standby_timeout(uint16_t standby_timeout) {
  if (millis() - previous_millis > standby_timeout) return true;
  return false;
}


static void fadeout(void) {
  fadeout_flag = 1;
  rgb_color rgb;
  for (uint8_t i = 255; i > 00; i--) {
      for (uint8_t z = 0; z < LED_COUNT; z++) {
        if (led_strip_colors[z].red > 1) led_strip_colors[z].red -= 1;
        if (led_strip_colors[z].green > 1) led_strip_colors[z].green -= 1;
        if (led_strip_colors[z].blue > 1) led_strip_colors[z].blue -= 1;
      }
      if (!vesc_standby_tacho()) return;
      update_strip();
  }
}


bool vesc_standby(void) {
  if (vesc_standby_tacho()) {
    if (vesc_standby_timeout(STANDBY_TIMEOUT)) { return true; }
    return false;
  }
  else {
    previous_tacho_value = bldc_get_tachometer_value();
    previous_millis = millis();
    fadeout_flag = 0;
    return false;
  }
}


void vesc_standby_lights(void) {
  if (fadeout_flag == 0)
    fadeout();

  if (!vesc_standby_tacho()) return;

  rgb_color current_rgb_color;
  uint16_t random_hue = generate_random_hue();
  current_rgb_color = hsvToRgb(random_hue, 255, 255);

  for (uint8_t i = 0; i < 255; i++) {
      current_rgb_color = hsvToRgb(random_hue, 255, cie[i]);
      for (uint8_t z = 0; z < LED_COUNT; z++) { led_strip_colors[z] = current_rgb_color; }
      update_strip();
  }
  if (!vesc_standby_tacho()) return;

  for (uint8_t i = 255; i > 40; i--) {
      current_rgb_color = hsvToRgb(random_hue, 255, cie[i]);
      for (uint8_t z = 0; z < LED_COUNT; z++) { led_strip_colors[z] = current_rgb_color; }
      update_strip();
      if (!vesc_standby_tacho()) return;
  }

}
