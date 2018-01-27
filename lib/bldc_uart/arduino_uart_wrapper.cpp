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
#include "arduino_uart_wrapper.h"


//https://www.arduino.cc/reference/en/language/functions/communication/serial/read/
//https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/HardwareSerial.h

 void serial_begin(long speed) {
    return Serial.begin(speed);
 }

 int serial_available(void) {
    return Serial.available();
 }

 int serial_write(unsigned char *data, unsigned int length) {
    return Serial.write(data, length);
 }


 int serial_read(void) {
    return Serial.read();
 }

unsigned int serial_print(char *data) {
    return Serial.print(data);
 }

unsigned int serial_println(char *data) {
    return Serial.println(data);
}

void do_delay(unsigned long time) {
    return delay(time);
}
