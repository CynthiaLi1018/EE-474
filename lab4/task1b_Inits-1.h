// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 1
// 08/03/21

// This is the header file for the task1b_Init.c. It was provide as the starter
// code for lab3 and is copied to lab4 since the same initialization was
// required.

#ifndef __TASK1B_Inits_H_
#define __TASK1B_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency
{
  PRESET1 = 120,  PRESET2 = 60,  PRESET3 = 12
};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes SW1, SW2.
void switchesInit(void);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

#endif // __TASK1B_Inits_H_