// _________ HEADER_1B _________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* HEADER_1B is task 1b's header file to intialize GPIO,
* specifically port F, J, and N. */

#ifndef __HEADER_1B__
#define __HEADER_1B__

// to set up GPIO
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

// to set up and change value of port F: LED4, LED3
#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 ))
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C ))
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC ))

// to set up and change value of port J: switch 2, switch 1
#define GPIODIR_J (*(( volatile uint32_t *) 0x40060400 ))
#define GPIODEN_J (*(( volatile uint32_t *) 0x4006051C ))
#define GPIODATA_J (*(( volatile uint32_t *) 0x400603FC ))
#define GPIOPUR_J (*(( volatile uint32_t *) 0x40060510 ))

// to set up and change value of port N: LED2, LED1
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C ))
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))

#endif //__HEADER_1B__