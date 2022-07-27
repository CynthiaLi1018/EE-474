// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 2a
// 8/9/21

// This is copied from Lab3 to Lab4 task 2a. 
// It is the header file that contains macros to acesss GPIO, Timer, ADC,
// interrupts, etc. registers that will be potentially used. It also contains
// the declarations of functions that will be used in the main function file.

#ifndef _TASK2A_H_
#define _TASK2A_H_

//----------------------GPIO------------------------------
#define RCGCGPIO        (*((volatile uint32_t *)0x400FE608))
// Port E addresses
#define GPIOAMSEL_E     (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E       (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E     (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E      (*((volatile uint32_t *)0x4005C3FC))

// Port J addresses
#define GPIODIR_J       (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J       (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J       (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J      (*((volatile uint32_t *)0x400603FC))

// Port A Address
#define GPIODIR_A       (*((volatile uint32_t *)0x40058400))
#define GPIODEN_A       (*((volatile uint32_t *)0x4005851C))

//--------------------Timer--------------------------------
#define RCGCTIMER       (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0       (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0       (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0      (*((volatile uint32_t *)0x40030004))
#define GPTMADCEV_0     (*((volatile uint32_t *)0x40030070))
#define GPTMTAILR_0     (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0       (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0       (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0       (*((volatile uint32_t *)0x40030024))

// Timer Configuation
#define GPTM0_16_32 0x1 // Enable 16/32 Timer 0
#define GPTM1_16_32 0x2 // Enable 16/32 Timer 1
#define GPTMA_DISABLE 0x0         // Disable Timer A
#define GPTMA_ENABLE 0x1          // Enable Timer A
#define TM_MODE_32 0x0            // Select 32-bit mode
#define TAMR_PER_TM_MODE 0x2      // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define TACDIR_COUNT_DOWN 0x10000 // Configure TACDIR bit of GPTMTAMR to count down
#define N16_MIL 0xF42400          // load the value 16,000,000
#define RESET_TA 0x1              // Reset timer

//-------------------ADC---------------------------
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

// -----------------------Interrupt-------------------------
#define GPTMIMR0        (*((volatile uint32_t *)0x40030018))
#define GPTMIMR1        (*((volatile uint32_t *)0x40031018))
#define GPIORIS_J       (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J       (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J        (*((volatile uint32_t *)0x40060410))

// Interrupt configuration
#define ADCIM (*((volatile uint32_t *)0x40038008))
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define ADCRIS (*((volatile uint32_t *)0x40038004))
#define ADCISC (*((volatile uint32_t *)0x4003800C))

#define INTERRUPT_ENABLE0 (*((volatile uint32_t *)0xE000E100))
#define INTERRUPT_ENABLE1 (*((volatile uint32_t *)0xE000E104))
#define TATOIM_ENABLE 0x1
#define INT_19_ENABLE 0x80000
#define INT_51_ENABLE 0x80000

// FSM traffice light, Moore Machine, 
void TrafficLight();

// initialize the Timer0
void GPTMInit();

// check if the timer reach to 1 sec, 
// return value is 0 (unreached) or 1 (if reached)
int one_second();

// input variable n to keep n seconds
void oneHertz(int n);

// reset the timer
void resetTimer();

// BELOW ARE FOUR LED PATTERN FUNCTIONS
// Turn on green light
void go();

// Turn on yellow light
void warn();

// Turn on red light
void stop();

// Turn off all lights
void off();

// create buttons and LEDs on LCD display
void LCD_Pattern();

// check if system switch is pressed, no input variable,
// return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable,
// return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

#endif //_TASK2A_H_