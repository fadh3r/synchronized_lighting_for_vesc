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

#include "vesc_uart.h"
#include "arduino_uart_wrapper.h"

// extern "C" {
  // Include libraries copied from VESC
  #include "datatypes.h"
  #include "buffer.h"
  #include "crc.h"
  #include "bldc_interface.h"
  /* bldc_interface.c and bldc_interface.h - These files can assemble the payload for all the commands
     that the VESC supports. They can also interpret packets from the VESC and extract
     the data from them. Notice that only the payload is handled in these files,
     not the start, stop, length and checksum bytes since these are different for the CAN interface.
  */
  #include "bldc_interface_uart.h"
  /* bldc_interface_uart.c and bldc_interface_uart.h - Connects packet and bldc_interface to provide a clean
  UART interface. This is where the user has to make the connection to the UART interface for the platform of choice.
  */
// };

// define pointer "mc_values_ptr" of type mc_values
mc_values *mc_values_ptr;

/* NOTE:
   bldc_interface.c - changed "send_buffer[]" size
   packet.h changed "PACKET_MAX_PL_LEN" size and "PACKET_HANDLERS" quantity
   bldc_interface_uart.c - commented #include "ch.h" and #include "hal.h"
*/

/* - datatypes.h - The data structures used by the VESC.
   - crc.c and crc.h - For calculating the CRC checksum
   - buffer.c and buffer.h - Helper functions for for going between C types and byte arrays. These are used by the bldc_interface files
   - packet.c and packet.h - For assembling the packets for the VESC with start, stop, length and checksum bytes. These
   files also have a state machine where one byte received from the VESC can be added at a time
   to assemble a packet and check the checksum correctness.
   - comm_uart.c - The connection between these files and the UART port is done in the file comm_uart.c,
   which is the file that you have to implement if you want to port this to a different platform.
*/


// The bldc_interface_uart files have three functions that have to be used:
// --bldc_interface_uart_init
// --bldc_interface_uart_process_byte - you could call bldc_interface_uart_process_byte directly from an interrupt handler every time you receive a byte.
// --bldc_interface_uart_run_timer



//user implementation of function that will send the bytes in *data with length len on the UART
static void send_packet(unsigned char *data, unsigned int len) {
  serial_write(data, len);
}


// Callback function for the received data from vesc
static void bldc_val_received(mc_values *val) {
  mc_values_ptr = val;
}


void comm_uart_init() {
  serial_begin(115200);
  // serial_print("Debug console started!");
  // Initialize the bldc interface and provide send function
  bldc_interface_uart_init(send_packet);
  // Give bldc_interface a callback function to call for handling the data when values are received.
  bldc_interface_set_rx_value_func(bldc_val_received);
}



/* Custom function to get actual values from VESC, based on Benjamin Vedder tutorial.
   Use values in bldc_val_received() callback function. */
void bldc_get_values(void) {
  /* Every time you want to read the realtime data you call the corresponding getter.
     This will send the get command to the VESC and return. When the data is received
     the callback will be called from the UART interface. */
  bldc_interface_get_values();

  //delay to give some time vesc to answer
  do_delay(10);

  while (serial_available()) {
    /* Call bldc_interface_uart_process_byte() function every time a byte is received on the UART
      with the received byte. It will run the state machine in the packet assembler and the callbacks in
      bldc interface will be called when the packets are ready.
      You could call bldc_interface_uart_process_byte directly from an interrupt handler every time you receive a byte. */
    bldc_interface_uart_process_byte(serial_read());
  }

  bldc_interface_uart_run_timer();
  //Call this function every millisecond to reset the packet state machine after a timeout in case data is lost.
}


/* get current VESC tachometer value */
long unsigned int bldc_get_tachometer_value(void) {
  return mc_values_ptr->tachometer;
}


/* Communicating is a uint8_t byte stream.
   First byte: "0x02" for packet length < 256 byte, second byte is for the packet length.
   Second byte: "0x03" for > 256 byte packet length, and next 2 bytes for the packet length.
   The follwing 2 bytes after the packet are the checksum. (see crc.h)
   The byte stream it terminated with a 0x03.
  */
