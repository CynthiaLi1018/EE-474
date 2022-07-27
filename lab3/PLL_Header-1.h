// Cynthia Li
// 1839952
// Lab 3 Task 1a
// 07/21/21

// This is the main function file of task 1a. It generates LED pattern
// that corresponds to the resistances.

#ifndef _PLL_HEADER_H_
#define _PLL_HEADER_H_

#include <stdint.h>

// ******************** CLOCK CONTROL REGISTERS ********************** //
#define MOSCCTL        (*(volatile uint32_t *)0x400FE07C)
#define RIS            (*(volatile uint32_t *)0x400FE050)
#define RSCLKCFG       (*(volatile uint32_t *)0x400FE0B0)
#define PLLFREQ0       (*(volatile uint32_t *)0x400FE160)
#define PLLFREQ1       (*(volatile uint32_t *)0x400FE164)
#define PLLSTAT        (*(volatile uint32_t *)0x400FE168)
#define MEMTIM0        (*(volatile uint32_t *)0x400FE0C0)

#endif // _PLL_HEADER_H_