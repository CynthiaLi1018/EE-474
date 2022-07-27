// Cynthia Li
// 1839952
// 7/16/2021
// This is the main function of task 2c. It fulfills the same functionality as
// task1b except uses interrupt to turn on/off LED instead of timer.

#include <stdint.h>
#include "task2c.h"

#define SYSTEM  0x1 
#define PED     0x2
#define RED     0x4 
#define YELLOW  0X8
#define GREEN   0x10

volatile unsigned char flag = 0x0; // 1 second counter
volatile unsigned char state = 0x0; // 5 second counter
volatile unsigned char button_held = 0x0; // 2 second counter

// possible states of the traffic light
enum TL_States { TL_SMStart, TL_stop, TL_warn, TL_go, TL_off } TL_State;

//Initialize LED
void LED_init(void) 
{
  volatile unsigned short delay = 0; // adds delay for register to set up
  RCGCGPIO |= 0x2000; // activate clock on port P
  delay++;
  delay++;  
         
  //Red LED
  GPIOAMSEL_L &= ~RED;         
  GPIODIR_L |= RED;     
  GPIOAFSEL_L &= ~RED;          
  GPIODEN_L |= RED;            
  
  //Yellow LED
  GPIOAMSEL_L &= ~YELLOW;        
  GPIODIR_L |= YELLOW;       
  GPIOAFSEL_L &= ~YELLOW;           
  GPIODEN_L |= YELLOW;            
  
  //Green LED
  GPIOAMSEL_L &= ~GREEN;         
  GPIODIR_L |= GREEN;    
  GPIOAFSEL_L &= ~GREEN;         
  GPIODEN_L |= GREEN;             
} 
 
// turn on red light connected to PL2 
void RED_on(void)
{ 
  GPIODATA_L |= RED; 
} 
 
// turn off red light connected to PL2
void RED_off(void) 
{
  GPIODATA_L &= ~RED; 
} 

// turn on yellow light connected to PL3
void YELLOW_on(void)
{ 
  GPIODATA_L |= YELLOW; 
} 
 
// turn off yellow light connected to PL3
void YELLOW_off(void) 
{
  GPIODATA_L &= ~YELLOW; 
} 

// turn on green light connected to PL4 
void GREEN_on(void)
{ 
  GPIODATA_L |= GREEN; 
} 
 
// turn off green light connected to PL4
void GREEN_off(void) 
{
  GPIODATA_L &= ~GREEN; 
}

//instantiates all the switches on and off board
void extern_switch_init(void)  
{ 
  volatile unsigned short delay = 0; // adds delay for register to set up
  RCGCGPIO |= 0x2000;   // Enable Port P Gating Clock
  delay++;     
  delay++;
  
  // SYSTEM button
  GPIOAMSEL_L &= ~SYSTEM;  // Disable PL0 analog function     
  GPIOAFSEL_L &= ~SYSTEM;  // Select PL0 regular port function     
  GPIODIR_L &= ~SYSTEM;    // Set PL0 to input direction     
  GPIODEN_L |= SYSTEM;     // Enable PL0 digital function 
  
  // PED button
  GPIOAMSEL_L &= ~PED;  // Disable PL1 analog function     
  GPIOAFSEL_L &= ~PED;  // Select PL1 regular port function     
  GPIODIR_L &= ~PED;    // Set PL1 to input direction     
  GPIODEN_L |= PED;     // Enable PL1 digital function 
}

// system pressed
unsigned long  SYSTEM_input(void) 
{   
  return (GPIODATA_L & SYSTEM); 
} 

// pedestrian pressed
unsigned long PED_input(void) 
{   
  return (GPIODATA_L & PED); 
} 

// creates FSM model for the states of traffic Light
void Traffic_Light()
{  
  // creates conditions to move to new state
  switch(TL_State) 
  {
  // case for start position
  case TL_SMStart:
    TL_State = TL_off;
    break;
  
  // case for on red LED
  case TL_stop:
    TL_State = TL_go;
    while (state != 0x5) { // if 5 second passes
      
    }
    break;
    
  // case for on yellow LED
  case TL_warn:
    TL_State = TL_stop;
    while (state != 0x5) { // if 5 second pass
      if (SYSTEM_input()) {
        if (button_held == 0x2) { // if 2 second pass
          TL_State = TL_off;
          button_held = 0x0;
          break;
        } 
      }
    }
    break;

  // case for on green LED
  case TL_go:
    TL_State = TL_stop;
    while (state != 0x5) { // if 5 second passs
      if (SYSTEM_input()) {
        if (button_held == 0x2) { // if 2 second pass
          TL_State = TL_off;
          button_held = 0x0;
          break;
        } 
      }
      if (PED_input()) {
        if (button_held == 0x2) { // if 2 second pass
          TL_State = TL_warn;
          button_held = 0x0;
          break;
        } 
      }
    }
    break;
    
  // case for when all LED off
  case TL_off:
    TL_State = TL_off;
    while (state != 0x5) { // if 5 second pass
      if (SYSTEM_input()) {
        if (button_held == 0x2) { // if 2 second pass
          TL_State = TL_stop;
          button_held = 0x0;
          break;
        } 
      }
    }
    break;
  }
  
  // Set up state actions for FSM
  switch(TL_State) {
  case TL_off:
    RED_off();
    YELLOW_off();
    GREEN_off();
    break;
      
  case TL_stop:
    RED_on();
    YELLOW_off();
    GREEN_off();
    break;
    
  case TL_warn:
    RED_off();
    YELLOW_on();
    GREEN_off();
    break;
    
  case TL_go:
    RED_off();
    YELLOW_off();
    GREEN_on();
    break;
  }
}

// Creates FSM for traffic light using interrupt
void main (void) {
  while(1) {
    state = 0x0; // resets 5 second counter whenever reentering FSM
    flag = 0x0; // resets 1 secong
    Traffic_Light();
  }
}