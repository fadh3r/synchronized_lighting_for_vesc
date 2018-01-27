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
#include <stdint.h>
#include "breathing_lights.h"
#include "color_shifting.h"

// tune "WHEEL_SIZE_RATIO" for velocity of color_pallete change
const uint8_t WHEEL_SIZE_RATIO = 15;
// time in standby before breating lights
const uint16_t STANDBY_TIMEOUT = 5000;

/* extern "C" - allows to use C header files with C++ code
    for more info see - https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c */
extern "C" {
  #include "vesc_uart.h"
};


// SETUP
void setup() {
  // UART Initialize
  comm_uart_init();
  // delay for vesc startup
  delay(2000);
}// END-OF-SETUP


void loop() {
// get values from VESC
bldc_get_values();
// bldc_interface_setters works only with disconnected PPM
//bldc_interface_set_current(2.00);
//bldc_interface_set_rpm(1000);

if (vesc_standby())
  vesc_standby_lights();
else
  update_strip_colors();

}// end-of-loop
