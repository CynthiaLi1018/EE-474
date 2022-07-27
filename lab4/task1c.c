// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 1
// 08/03/21

// This is the main function file for task 1c, it contains switch functions'
// and LCD_Pattern's definition. It is able to create two virtual buttons and
// set system clock frequency based on the press/not pressed condition of the
// two buttons. It will read the board temperature and display the temperature
// value in Celsius and Fahrenheit and the current system clock frequency on 
// LCD display.

#include "task1c_inits.h"
#include "task1c.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include <stdint.h>
#include <stdio.h>

uint32_t ADC_value;
enum frequency freq;
int updateTemp = 0;

bool SW1(int x, int y) {
  return ((x >= 950) && (x <= 1450) && (y >= 950) && (y <= 1350));
}

bool SW2(int x, int y) {
  return ((x >= 1600) && (x <= 1950) && (y >= 950) && (y <= 1350));
}

void ADC0SS3_Handler(void) {
   ADCISC_0 |= SS3_INTERRUPT_CLEAR; // clear the interrupt flag
   ADC_value = ADCSSFIFO3_0 & 0xFFF; // save adc value to global variable
   updateTemp = 1; // raise flag
}

void LCD_Pattern(float temp_c, float temp_f, int currentFreq) {
   // create buttons: bright blue for SW1, bright red for SW2
  LCD_DrawFilledRect(32, 120, 100, 60, Color4[9]); 
  LCD_DrawFilledRect(192, 120, 100, 60, Color4[12]);
  // print labels for the switches
  LCD_SetCursor(75, 145);
  LCD_Printf("SW1");
  LCD_SetCursor(230, 145);
  LCD_Printf("SW2");
  // print on LCD display
  LCD_SetCursor(0, 0);
  LCD_Printf("The current temperature is ");
  LCD_PrintFloat(temp_c);
  LCD_Printf(" C, ");
  LCD_PrintFloat(temp_f);
  LCD_Printf(" F. \r\n");
  LCD_Printf("The current clock frequency is ");
  LCD_PrintInteger(currentFreq);
  LCD_Printf(" MHz.  \r\n");
}

int main(void) {
  freq = PRESET2;        // Select system clock frequency preset 
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadPot_Init();     // Initialize ADC0 to read from temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  LCD_Init();            // Initialize the LCD display
  Touch_Init();          // Initialize the touch screen
  
  float temp_c;
  float temp_f;
  int currentFreq;
  
  while (1) {
    // clear flag
    updateTemp = 0;
    
    //touch screen to set frequency
    int x = Touch_ReadX();
    int y = Touch_ReadY();
    if (SW1(x, y)) {
      freq = PRESET3;
    } else if (SW2(x, y)) {
      freq = PRESET1;
    }
    
    // determing display frequency
    if (freq == PRESET1) {
      currentFreq = 120;
    } else if (freq == PRESET2) {
      currentFreq = 60;
    } else if (freq == PRESET3) {
      currentFreq = 12;
    } else { // error
      currentFreq = 0;
    }
    
    // convert ADC values into floating point values
    temp_c = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    temp_f = temp_c * 9 / 5 + 32;
    
    LCD_Pattern (temp_c, temp_f, currentFreq);
    
    // wait for flag
    while (updateTemp != 1);
  }
  return 0;
}

