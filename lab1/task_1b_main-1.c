// _________ MAIN PROGRAM_________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* The program allows two internal user input, SW1 to control LED1, SW2 to 
* control LED2. When button is pressed, LED should lit, otherwise it it be
* turned off. */

#include <stdint.h>
#include "task_1b.h"

int main (void) {
   volatile unsigned short delay = 0 ;
   RCGCGPIO |= 0x100; // Enable PortJ GPIO
   RCGCGPIO |= 0x1000; // Enable PortN GPIO
   
   // Delay 2 more cycles before access Timer registers
   delay++; 
   delay++; 
    
   GPIODIR_N |= 0x3; // Set PN0, PN1 to output
   GPIODEN_N |= 0x3; // Set PN0, PN1 to digital port   // D1, D2

   GPIODIR_J |= 0x0; // Set PJ0, PJ1 to input
   GPIOPUR_J |= 0x3; // Enable the pull-up resistor for PJ0, PJ1
   GPIODEN_J |= 0x3; // Set PJ0, PJ1 to digital port   // SW1, SW2
   
   GPIODIR_F = 0x11; // Set PF4, PF0 to output
   GPIODEN_F = 0x11; // Set PF4M PF0 to digital port
   GPIODATA_F = 0X0; // turns off D3, D4
   
   while (1) {
     if ((GPIODATA_J & 0x3) == 0 ) {    // both switches are pessed
        GPIODATA_N = 0x3;    // D1, D2 both turn on
      }
     else if ((GPIODATA_J & 0x3) == 1) {    // Only SW2 is pressed
        GPIODATA_N = 0x1;    // D2 is turned on
      }
     else if ((GPIODATA_J & 0x3) == 2) {     // Only SW1 is pressed
         GPIODATA_N = 0x2;    // D1 is turned on
      }
     else if ((GPIODATA_J & 0x3) == 3) {   // neither switch is pressed
         GPIODATA_N = 0x0;    // D1, D2 are turned off
      }
   }
}