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

#ifndef VESC_UART_H
#define VESC_UART_H

    //declare global "mc_values_ptr" pointer of type "mc_values" for received from VESC data
    //dox - https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files
    #include "bldc_interface.h"
    extern mc_values *mc_values_ptr;

    void bldc_get_values(void);
    void comm_uart_init(void);
    long unsigned int bldc_get_tachometer_value(void);

#endif /* VESC_UART_H */
