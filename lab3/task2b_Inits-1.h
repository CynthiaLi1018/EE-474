// Cynthia Li
// 1839952
// Lab 3 Task 2b
// 07/25/21

// This is the header file for the task2b_inits.c. It now only contains the 
// initialization function for PLL and UART3.

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes UART3
void UART_Init(void);

#endif  // _Lab3_Inits_H_