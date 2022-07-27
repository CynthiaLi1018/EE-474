// Cynthia Li
// 1839952
// 07/15/21
// This is the main function for task 2a. It periodically turns on and then off
// the LED4 to LED1 at 1Hz frequency using a interrupt.

#include <stdint.h>
#include "task2a.h"

#define PF0 0x01 // D4
#define PF4 0x10 // D3
#define PN0 0x1 // D2
#define PN1 0x2 // D1

// GPTMInit initializes timer 0A at the count down mode
void GPTMInit()
{
  RCGCTIMER |= GPTM0_16_32;       // Enable Timer 0
  GPTMCTL0 = GPTMA_DISABLE;       // Disable Timer A
  GPTMCFG0 = TM_MODE_32;          // Select 32-bit mode
  GPTMTAMR0 |= TAMR_PER_TM_MODE;  // Set periodic timer mode
  GPTMTAMR0 &= ~TACDIR_COUNT_UP;  // Configure TACDIR to count down
  GPTMTAILR0 = N16_MIL;           // Load value of 16 million into GPTMTAILR
  GPTMCTL0 |= GPTMA_ENABLE;       // Enable Timer A
}

// GPIOPortInit initializes GPIO Port F/N's LED to output
void GPIOPortInit()
{
  // Enable N, F port
  RCGCGPIO |= Port_N;
  RCGCGPIO |= Port_F;
  
  // Enable PN0, PN1, PF0, PF4
  GPIODEN_N |= PN0;
  GPIODEN_N |= PN1;
  GPIODEN_F |= PF0;
  GPIODEN_F |= PF4;

  // Set PN0, PN1 as input, PF0, PF4
  GPIODIR_N |= PN0;
  GPIODIR_N |= PN1;
  GPIODIR_F |= PF0;
  GPIODIR_F |= PF4;
}

// interruptInit inializes the interrupt
void interruptInit()
{
  GPTMIMR0 = TATOIM_ENABLE;            // Enable Timer A Time-Out Interrupt
  INTERRUPT_ENABLE0 |= INT_19_ENABLE;  // Enable interrupt 19
}

// oneHertz count every second and return int to indicate whether the second
// has passed
int oneHertz()
{
  if (GPTMRIS0 & 0x1 == 0x1)
  {
    GPTMICR0 |= 0x1; // reset timer
    return 1;       // 1 second has finished
  }
  else
  {
    return 0; // 1 second has not yet finished
  }
}

// determines the light behavior
void Timer0A_Handler()
{
  // turn on/off D4
  GPIODATA_F |= 0x01;
  while (!oneHertz()) {}
  GPIODATA_F = 0x0;
  while (!oneHertz()) {}
  
  // turn on/off D3
  GPIODATA_F |= 0x10;
  while (!oneHertz()) {}
  GPIODATA_F = 0x0;
  while (!oneHertz()) {}
    
  // turn on/off D2
  GPIODATA_N |= 0x1;
  while (!oneHertz()) {}
  GPIODATA_N = 0x0;
  while (!oneHertz()) {}
   
  // turn on/off D1
  GPIODATA_N |= 0x2;
  while (!oneHertz()) {}
  GPIODATA_N = 0x0;
  while (!oneHertz()) {}
  
  GPTMICR0 |= 0x1; // reset timer
}

// determine timer status
int isReached()
{
  return (GPTMRIS0 & 0x1);
}

void main()
{
  GPIOPortInit();
  GPTMInit();
  interruptInit();
  while (1) {}
}