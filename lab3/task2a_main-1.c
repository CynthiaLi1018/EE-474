// Cynthia Li
// 1839952
// Lab 3 Task 2a
// 07/25/21

// This is the main function file of task 2a.
// It is the same as task 1b only that I've enabled UART0 to send the data
// from TIVA to the computer terminal.

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "task2a_Init.h"
#include "task2a.h"

uint32_t ADC_value;
int updateTemp = 0;

void ADC0SS3_Handler(void) {
   ADCISC_0 |= SS3_INTERRUPT_CLEAR; // clear the interrupt flag
   GPTMICR_0 |= 0x1; // clear timer interrupt flag
   ADC_value = ADCSSFIFO3_0 & 0xFFF; // save adc value to global variable
   updateTemp = 1;
}

void PortJ_Handler(void) {
   GPIOICR_J |= 0x3; // Clear Port J interruption
  enum frequency freq = PRESET2;
  if (GPIODATA_J == SW1MASK) {
    freq = PRESET3; // 12 MHz
  } else if (GPIODATA_J == SW2MASK) {
    freq = PRESET1; // 120 MHz
  }
  PLL_Init(freq);
}

int main(void) {
  enum frequency freq = PRESET2; // Select system clock frequency to 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  SW_Init();             // Initialize the 2 on-board SWs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART_Init();           // Initialize UART0 to communicate with computer
  float temperature;
  char output_text[7];   // temporary string to store output text display
  
  while (1) {
    updateTemp = 0;
    temperature = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    temperature = roundf(temperature * 100) / 100;
    sprintf(output_text, "%.2f\r\n", temperature);
    for (int i = 0; i < 7; i++) {
      UARTDR_0 = output_text[i];
    }
    while (updateTemp != 1);
  }
  return 0;
}