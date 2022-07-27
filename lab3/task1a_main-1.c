// Cynthia Li
// 1839952
// Lab 3 Task 1a
// 07/21/21

// This is the main function file of task 1a. I've It generates LED pattern
// that corresponds to the resistances.

#include <stdint.h>
#include "task1a_Inits.h"
#include "task1a.h"

uint32_t ADC_value;

void ADC0SS3_Handler(void)
{ 
  ADCISC |= 0x8;          // 4.1: Clear the ADC0 interrupt flag
  GPTMICR_0 |= 0x1;       // clear timed out
  ADC_value = ADCSSFIFO3; // 4.2: Save the ADC value to global variable ADC_value
}

void D1_on()
{
  GPIODATA_N |= 0x2; // turn on D1
}

void D1_off()
{
  GPIODATA_N &= ~0x2; // turn off D1
}

void D2_on()
{
  GPIODATA_N |= 0x1; // turn on D2
}

void D2_off()
{
  GPIODATA_N &= ~0x1; // turn off D2
}

void D3_on()
{
  GPIODATA_F |= 0x10; // turn on D3
}

void D3_off()
{
  GPIODATA_F &= ~0x10; // turn off D3
}

void D4_on()
{
  GPIODATA_F |= 0x1; // turn on D4
}

void D4_off()
{
  GPIODATA_F &= ~0x1; // turn off D4
}

int main(void)
{
  enum frequency freq = PRESET2; // // Select system clock frequency to 60 MHz
  PLL_Init(freq);                // Set system clock frequency to 60 MHz
  LED_Init();                    // Initialize the 4 onboard Ds (GPIO)
  ADCReadPot_Init();             // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init();         // Initialize Timer0A to trigger ADC0
  float resistance;

  while (1)
  {                                             // STEP 5: Change the pattern of Ds based on the resistance.
    resistance = (ADC_value / 4095.0) * 10.0; // 5.1: Convert ADC_value to resistance in kilo-ohm
    if (resistance < 2.5)
    { // 5.2: Change the pattern of LEDs based on the resistance
      D1_on();
      D2_off();
      D3_off();
      D4_off();
    }
    else if (resistance < 5.0)
    {
      D1_on();
      D2_on();
      D3_off();
      D4_off();
    }
    else if (resistance < 7.5)
    {
      D1_on();
      D2_on();
      D3_on();
      D4_off();
    }
    else
    {
      D1_on();
      D2_on();
      D3_on();
      D4_on();
    }
  }
  return 0;
}