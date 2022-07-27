// _________ MAIN PROGRAM_________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* The program controls LED4-1 to lit periodically with a pattern that
* D4-1 turn on one by one and then turn off one by one with 0.3 second
* delay between each on/off action. */

// include library for int and header file
#include <stdint.h>
#include "task_1a.h"

int main ( void ) {
   volatile unsigned short delay = 0;
   
   RCGCGPIO |= 0x20; // Enable PortF GPIO
   RCGCGPIO |= 0x1000; // Enable PortN GPIO
   
   delay ++; // Delay 2 more cycles before access Timer registers
   delay ++; // Refer to Page. 756 of Datasheet for info
   
   GPIODIR_F = 0x11; // Set PF4, PF0 to output
   GPIODEN_F = 0x11; // Set PF4 , PF 0 to digital port   // D4, D3
  
   GPIODIR_N = 0x3; // Set PN1, PN0 to output
   GPIODEN_N = 0x3; // Set PN1, PN0 to digital port   // D2, D1
  
   while ( 1 ) {
      // turn on D4-1 one at a time with .3s delay between each action
      GPIODATA_F = 0x1; // Set PF0 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_F = 0x11; // Set PF4 to 1}
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x1; // Set PN0 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x3; // Set PN1 to 1
      for (int j = 0; j < 1000000; j++) {}
      
      // turn off D4-1 one at a time with .3s delay between each action
      GPIODATA_F = 0x10; // Set PF0 to 0
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_F = 0x0; // Set PF4 to 0
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x2 ; // Set PN0 to 0
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x0; // Set PN1 to 0
      for (int j = 0; j < 1000000; j++) {}
   }
}