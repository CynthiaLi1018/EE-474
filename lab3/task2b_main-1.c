// Cynthia Li
// 1839952
// Lab 3 Task 2b
// 07/25/21

// This is the main function file. It defines the returnToSender function to
// process data from input to UART.

#include <stdint.h>
#include "task2b_Inits.h"
#include "task2b.h"

int main(void) {
  enum frequency freq = PRESET2; // Select system clock frequency 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  UART_Init();           // Initialize UART3 to communicate with computer
  while (1) {
    ReturnToSender();
  }
  return 0;
}

void ReturnToSender() {
  char input;
  while ((UARTFR_3 & 0x40) == 0x0); // wait for Rx to be full
  input = UARTDR_3;
  while ((UARTFR_3 & 0x80) == 0x0); // wait for Tx to be empty
  UARTDR_3 = input;
  if (input == '\r') {
    UARTDR_3 = '\n';
  }
}