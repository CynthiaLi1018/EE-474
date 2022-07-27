// Cynthia Li
// 1839952
// 07/15/21
// This is the main function for task 2b. It periodically turn on and off LED1
// at 1Hz frequency, when SW1 is pressed, it will let LED1 stay at current
// state and LED2 will turn on, when SW2 is pressed, LED2 will turn off, and
// LED1 will go back to the periodic shining

#include <stdint.h>
#include "task2b.h"

#define SW1 0x02
#define SW2 0x01
#define D1 0x02
#define D2 0x01

// GPIOInit initializes GPIO Port J/N to set LED to output and switch to input
// it also initializes the interrupt for port J
void GPIOInit() {
  GPIODIR_J = 0x0;         // Set PJ0 and PJ1 to input
  GPIODIR_N = (D1 | D2);   // Set PN0 and PN1 to output
  GPIODEN_J = (SW1 | SW2); // Set PJ0 and PJ1 to digital
  GPIODEN_N = (D1 | D2);   // Set PN0 and PN1 to digital
  GPIOPUR_J = (SW1 | SW2); // Set up pullup resistors
  
  EN1 = PORTJ_INTERRUPT_EN; // Enable Port J Interruption
  GPIOIM_J = 0x0;           // Mask all interrupts
  GPIOIS_J &= ~0x3;         // Make bits 1 and 0 edge sensitive
  GPIOIBE_J &= ~0x3;        // Deactivate both edge detection
  GPIOIEV_J &= ~0x3;        // Falling edge
  GPIOICR_J |= 0x3;         // Clear Port J interruption
  GPIOIM_J |= 0x3;          // Unmask bits 1 and 0
}

// GPTMInit initializes timer 0A at the count down mode
void TimerInit() {
  RCGCTIMER |= RCGCTIMER_0;        // Enable timer 0
  GPTMCTL_0 = 0x0;                 // Disable timer 0
  GPTMCFG_0 = CFG_32BIT;           // Set 32-bit mode
  GPTMTAMR_0 |= TAMR_PERIODIC;     // Set timer to periodic
  GPTMTAMR_0 |= TAMR_COUNT_DOWN;   // Set timer to  countdown
  GPTMTAILR_0 = FREQ_1HZ;          // Set frequency to 1Hz
  GPTMCTL_0 = 0x1;                 // Enable timer 0;
}

// PortJ_Handler defines the interrupt behavior to turn on LED2 and respond to
// switch 2
void PortJ_Handler() {
  if (GPIODATA_J == SW2) {
    GPTMCTL_0 = 0x1; // Enable timer 0;
    GPIODATA_N &= !D2; // Turn off LED2
  } else if (GPIODATA_J == SW1) {
    GPTMCTL_0 = 0x0; // Disable timer 0;
    GPIODATA_N |= D2; // Turn on LED2
  }
  GPIOICR_J |= 0x3; // Clear Port J interruption
}

int main (void) {
  volatile unsigned short delay = 0 ;
  RCGCGPIO |= RCGCGPIO_J_EN; 
  RCGCGPIO |= RCGCGPIO_N_EN;
  delay++; // Delay 2 more cycles before access Timer registers
  delay++;
  
  GPIOInit();
  TimerInit();
  
  while (1) { 
    GPIOICR_J |= 0x3; // Clear Port J interruption
    GPTMICR_0 = 0x01; // clear the TATORIS bit;
    GPTMICR_0 = 0x00;
    GPIODATA_N |= D1; // Turn on D1
    
    while (!(GPTMRIS_0 & 0x1)); // 1 second timer
   
    GPTMICR_0 = 0x01; // clear the TATORIS bit;
    GPTMICR_0 = 0x00;
    GPIODATA_N &= !D1; // Turn off D1
    
    while (!(GPTMRIS_0 & 0x1));  // 1 second timer
  }
}
