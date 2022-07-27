// _________ HEADER_2 _________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* HEADER_1B is task 2's header file to intialize GPIO,
* specifically port M to allow external button and LED
* input and output */

#ifndef __HEADER_2__
#define __HEADER_2__

// to set up GPIO
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

// to set up GPIO port L
#define GPIOAMSEL_M (*(( volatile uint32_t *) 0x40063528 ))
#define GPIOAFSEL_M (*(( volatile uint32_t *) 0x40063420 ))
#define GPIODIR_M (*(( volatile uint32_t *) 0x40063400 ))
#define GPIODEN_M (*(( volatile uint32_t *) 0x4006351C ))
#define GPIODATA_M (*(( volatile uint32_t *) 0x400633FC ))

#endif    // __HEADER_2__

