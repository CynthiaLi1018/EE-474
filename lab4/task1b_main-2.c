// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 1
// 08/03/21

// This is the main function file for task 1b. It uses two on-board switches to
// select the system clock frequency and reads the temperature of the board. It 
// prints the read temperature in Celsius and Fahrenheit and the
// current frequency to LCD display.

#include <stdint.h>
#include <stdio.h>
#include "PLL_Header.h"
#include "task1b_inits.h"
#include "task1b.h"
#include "SSD2119_Display.h"

uint32_t ADC_value;
float temp_c;
float temp_f;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

void ADC0SS3_Handler(void)
{
  ADCISC |= 0x8;          // Clear the ADC0 interrupt flag
  GPTMICR_0 |= 0x1;       // Clear timed out
  ADC_value = ADCSSFIFO3; // Save the ADC value to global variable ADC_value
  // calculate temperature in Celsius and Fahrenheit.
  temp_c = 147.5 - ((75.0 * (3.3 - 0.0) * ADC_value) / 4096.0);
  temp_f = (temp_c * 1.8) + 32.0;
  
  if (SW2_press())
  {
    freq = PRESET3;         // Set system clock frequency to 12 MHz
    PLL_Init(freq);
    GPTMTAILR_0 = 0xB71B00; // Set max count down value to 12 million
    TimerADCTriger_Init();
  }
  
  if (SW1_press())
  {
    freq = PRESET1;          // Set system clock frequency to 120 MHz
    PLL_Init(freq);
    GPTMTAILR_0 = 0x7270E00; // Set max count down value to 120 million
    TimerADCTriger_Init();
  }
  
  // the print text on LCD display
  LCD_SetCursor(0,0);
  LCD_Printf("The current Temperature is ");
  LCD_PrintFloat(temp_c);
  LCD_Printf(" C, ");
  LCD_PrintFloat(temp_f);
  LCD_Printf(" F.\n");
  LCD_Printf("The current clock frequency is %d MHz.", freq);
}

unsigned long SW1_press()
{
  return !(GPIODATA_J & 0x1);
}

unsigned long SW2_press()
{
  return !(GPIODATA_J & 0x2);
}

int main()
{
  PLL_Init(freq);        // Set system clock frequency to 12 MHz
  switchesInit();        // Initialize SW1, SW2 (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the internal temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
 
  while (1) {}
  return 0;
}