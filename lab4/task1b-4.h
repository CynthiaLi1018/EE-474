// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 1
// 08/03/21

// This is the header file for task 1b, it is copied from Lab 3. 
// It has defined the macros to access GPIO registers, timer and ADC.
// It has also declared two functions to check whether the 2 on-board switch
// is pressed.

#ifndef __TASK1B_H__
#define __TASK1B_H__

//------------------GPIO----------------------------
#define RCGCGPIO        (*((volatile uint32_t *)0x400FE608))
// Port E
#define GPIOAMSEL_E     (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E       (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E     (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E      (*((volatile uint32_t *)0x4005C3FC))
// Port J 
#define GPIODIR_J       (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J       (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J       (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J      (*((volatile uint32_t *)0x400603FC))

//------------------TIMER----------------------
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMADCEV_0 (*((volatile uint32_t *)0x40030070))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

//------------------ADC----------------------
#define RCGCADC (*((volatile uint32_t *)0x400FE638))

#define ADCCC (*((volatile uint32_t *)0x40038FC8))
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
#define ADCACTSS (*((volatile uint32_t *)0x40038000))
#define ADCEMUX (*((volatile uint32_t *)0x40038014))
#define ADCSSEMUX3 (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0))
#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4))
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8))

#define ADCIM (*((volatile uint32_t *)0x40038008))
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define ADCRIS (*((volatile uint32_t *)0x40038004))
#define ADCISC (*((volatile uint32_t *)0x4003800C))

// check if switch1 is pressed, 
// return value is 0 (unpreessed) or 1 (if pressed)
unsigned long SW1_press();

// check if switch2 is pressed,
// return value is 0 (unpreessed) or 1 (if pressed)
unsigned long SW2_press();

#endif // __TASK1B_H__