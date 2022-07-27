// Cynthia Li
// 1839952
// 7/16/2021
// This is the header file for task2c. It defines macros to memory address of
// GPIO L port, timer, interrupt, and helper functions to control traffic light

#ifndef __TASK_2C_H__ 
#define __TASK_2C_H__

// RCGPCGPIO
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

// macros for accessing GPIO L ports
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCGPIO_L_EN 0x00000400

#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))

// Timer
#define RCGCTIMER	 (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_TIMER0	 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_TIMER0	 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_TIMER0	 (*((volatile uint32_t *)0x40030004))

#define GPTMTAILR_TIMER0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_TIMER0	 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_TIMER0	 (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_TIMER0	 (*((volatile uint32_t *)0x40030018))

// Interrupts
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define EN1 (*((volatile uint32_t *)0xE000E104))
#define EN2 (*((volatile uint32_t *)0xE000E108))

// initialize LED
void LED_init();

// helper functions to turn on LED
void RED_on(void);
void YELLOW_on(void);
void GREEN_on(void);

// helper functions to turn off LED
void RED_off(void);
void YELLOW_off(void);
void GREEN_off(void);

// initialize timer0
void timer_init();

// initialize extern switches
void extern_switch_init();

// helper function to get input from switch
unsigned long SYSTEM_input();
unsigned long PED_input();

// FSM for traffic light
void Traffic_Light();

#endif //__HEADER_2C_H__