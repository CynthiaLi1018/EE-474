// Cynthia Li
// 1839952
// Lab 3 Task 1a
// 07/22/21

// This is the header file for the task1a_main.c. It is provide as the starter
// code. It defines the macros to configure on-board ADC0 and Timer 0A and to
// access the 2 on-board switches.

#ifndef __TASK1A_H__
#define __TASK1A_H__

//------------------GPIO----------------------
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_F 0x20
#define Port_N 0x1000
#define Port_E 0x10

// Port F Address
#define GPIODIR_F       (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F       (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F      (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N       (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N       (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N      (*((volatile uint32_t *)0x400643FC))

// Port E Address
#define GPIODIR_E       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E       (*((volatile uint32_t *)0x4005C51C))
#define GPIODATA_E      (*((volatile uint32_t *)0x4005C3FC))
#define GPIOAMSEL_E     (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E     (*((volatile uint32_t *)0x4005C420))

// Port J Address
#define GPIODEN_J       (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J       (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J       (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J      (*((volatile uint32_t *)0x400603FC))

// Port F Control
#define PF0 0x01 // connect to LED4
#define PF4 0x10 // connect to LED3

// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1

// Port E Control
#define PE0 0x1
#define PE1 0x2
#define PE2 0x4
#define PE3 0x8

//------------------TIMER----------------------
#define RCGCTIMER       (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0       (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0       (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0      (*((volatile uint32_t *)0x40030004))
#define GPTMADCEV_0     (*((volatile uint32_t *)0x40030070))
#define GPTMTAILR_0     (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0       (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0       (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0       (*((volatile uint32_t *)0x40030024))

//------------------ADC----------------------
#define RCGCADC         (*((volatile uint32_t *)0x400FE638))
#define ADCACTSS        (*((volatile uint32_t *)0x40038000))
#define ADCEMUX         (*((volatile uint32_t *)0x40038014))
#define ADCSSCTL3       (*((volatile uint32_t *)0x40080A4))
#define ADCIM           (*((volatile uint32_t *)0x40038008))
#define ADCSSFIFO3      (*((volatile uint32_t *)0x400380A8))
#define ADCISC          (*((volatile uint32_t *)0x4003800C))
#define ALTCLKCFG       (*((volatile uint32_t *)0x400FE138))
#define ADCCC           (*((volatile uint32_t *)0x40038FC8))

#define ADCSSEMUX3      (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3       (*((volatile uint32_t *)0x400380A0))

//------------------INTERRUPT----------------------
#define GPTMIMR0        (*((volatile uint32_t *)0x40030018))
#define GPTMIMR1        (*((volatile uint32_t *)0x40031018))
#define GPIORIS_J       (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J       (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J        (*((volatile uint32_t *)0x40060410))

#define INTERRUPT_ENABLE0 (*((volatile uint32_t *)0xE000E100))
#define INTERRUPT_ENABLE1 (*((volatile uint32_t *)0xE000E104))
#define TATOIM_ENABLE 0x1
#define INT_19_ENABLE 0x80000
#define INT_51_ENABLE 0x80000

//controll the LED1 ON/OFF
void D1_on();
void D1_off();

//controll the LED2 ON/OFF
void D2_on();
void D2_off();

//controll the LED3 ON/OFF
void D3_on();
void D3_off();

//controll the LED4 ON/OFF
void D4_on();
void D4_off();

#endif  //__TASK1A_H__