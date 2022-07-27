// Cynthia Li
// 1839952
// 07/15/21
// This is the header file for task 2b. It defines the macros to
// memory addresses for GPIO J/N, timer, interrupt and helper functions.

#ifndef __TASK_2B_H__
#define __TASK_2B_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCGPIO_J_EN 0x100
#define RCGCGPIO_N_EN 0x1000

// Port N
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port J
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIOIS_J (*((volatile uint32_t *)0x40060404))
#define GPIOIBE_J (*((volatile uint32_t *)0x40060408))
#define GPIOIEV_J (*((volatile uint32_t *)0x4006040C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define GPIORIS_J (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))

// Timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define RCGCTIMER_0 0x01
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define TAMR_PERIODIC 0x0002
#define TAMR_COUNT_DOWN 0x0000
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define CFG_32BIT 0x00
#define FREQ_1HZ 0xF42400 // 16M in hex

// interrupt
#define EN1 (*((volatile uint32_t *)0xE000E104))
#define PORTJ_INTERRUPT_EN 0x00080000

// helper function to initialize GPIO
void GPIOInit();
// helper function to initialize Timer
void TimerInit();
// switches' ISR
void PortJ_Handler();

#endif //__TASK_2B_H__