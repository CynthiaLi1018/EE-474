// _________ HEADER_1A _________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* HEADER_1A is task 1a's header file to intialize GPIO,
* port F and port N. */

#ifndef __HEADER_1A__
#define __HEADER_1A__

// to set up GPIO
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

// to set up and change data of GPIO port F: LED4, LED3
#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 ))
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C ))
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC ))

// to set up and change data of GPIO port N: LED2, LED1
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C ))
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))

#endif //__HEADER_1A_
