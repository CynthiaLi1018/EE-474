// Cynthia Li
// 1839952
// 07/10/21
// This is the header file for task 1a. It defines the macros to
// memory addresses for GPIO F/N and helper functions.

#ifndef __HEADER_1A_H__
#define __HEADER_1A_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Port F Address
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCFG0 (*((volatile uint32_t *)0x40030000))
#define GPTMCTL0 (*((volatile uint32_t *)0x4003000C))
#define GPTMTAMR0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR0 (*((volatile uint32_t *)0x40030024))

// Timer Configuation
#define GPTM0_0 0x1               // Enable Timer 0
#define GPTMA_DISABLE 0x0         // Disable Timer A
#define GPTMA_ENABLE 0x1          // Enable Timer A
#define TM_MODE_32 0x0            // Select 32-bit mode
#define TAMR_PER_TM_MODE 0x2      // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define TACDIR_COUNT_DOWN 0x10000 // Configure TACDIR bit of GPTMTAMR to count down
#define N16_MIL 0xF42400          // load the value 16,000,000

// initialize Timer
void GPTMInit();

// initialize GPIO
void GPIOPortInit();

// count for one second
int oneHertz();

#endif //__HEADER_1A_H__