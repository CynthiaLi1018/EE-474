// Cynthia Li
// 1839952
// 07/10/21
// This is the main function for task 1a. It periodically turns on and then off
// LED4 to LED1 on the TIVA board at 1Hz frequency using a timer

#include <stdint.h>
#include "task1a.h"

// GPTMInit initializes timer 0A at the count down mode
void GPTMInit()
{
  RCGCTIMER |= GPTM0_0;      // Enable 16/32 Timer 0
  GPTMCTL0 = GPTMA_DISABLE;      // Disable Timer A
  GPTMCFG0 = TM_MODE_32;         // Select 32-bit mode
  GPTMTAMR0 |= TAMR_PER_TM_MODE; // Set periodic timer mode
  GPTMTAMR0 &= ~TACDIR_COUNT_UP; // Configure TACDIR to count down
  GPTMTAILR0 = N16_MIL;          // Load value of 16 million into GPTMTAILR0
  GPTMCTL0 |= GPTMA_ENABLE;      // Enable Timer A
}

// GPIOPortInit initializes GPIO Port F/N's LED to input
void GPIOPortInit()
{
  // Enable port F, N
  RCGCGPIO |= 0x20;
  RCGCGPIO |= 0x1000;
  
  // Enable PF0, PF4, PN0, PN1
  GPIODEN_F |= 0x01;
  GPIODEN_F |= 0x10;
  GPIODEN_N |= 0x01;
  GPIODEN_N |= 0x02;
  
  // Set PN0, PN1, PF0, PF4 as output
  GPIODIR_N |= 0x3;
  GPIODIR_F |= 0x11;
}

// oneHertz uses timer to count for 1 second
int oneHertz()
{
  if (GPTMRIS0 & 0x1 == 0x1)
  {
    GPTMICR0 |= 0x1; // reset timer
    return 1;        // 1 second has passed
  }
  else
  {
     return 0;      // less than 1 second
  }
}

void main()
{
  GPIOPortInit();
  GPTMInit();
  while (1)
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
  }
}