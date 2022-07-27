// Cynthia Li
// 1839952
// 7/11/2021
// This is the main function of task 1b. It fulfills the same functionality as
// lab1 task2 except it prolongs the light switch period to 5 seconds and 
// required 2 second long press to be considered as a valid switch input.

#include <stdint.h>
#include "task1b.h"

#define SYSTEM  0x1 
#define PED     0x2
#define RED     0x4 
#define YELLOW  0X8
#define GREEN   0x10

int count; //time counter
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

// system_button_check determines whether system button undergoes a long
// enough press to change state
void system_button_check() {
  while (SYSTEM_input()) {
    if ((GPTMRIS_TIMER0 & 0x1) == 1) {
      count++;
      GPTMICR_TIMER0 |= 0x1;  // reset timer
      // check if button is held for 2 sec
      if (count >= 2) {
        TL_State = TL_off;
        GPTMICR_TIMER0 = 0x1; // reset timer
        break;
      }
    }
  }
}

// ped_button_check determines whether system button undergoes a long
// enough press to change state
void ped_button_check() {
  while (PED_input()) {
    if ((GPTMRIS_TIMER0 & 0x1) == 1) { // 1 second pass
      count++;
      GPTMICR_TIMER0 |= 0x1;
      // if button is pressed for longer than 2 seconds
      if (count >= 2) {
        TL_State = TL_warn;
        GPTMICR_TIMER0 = 0x1;
        break;
      }
    }
  }
}

// neither_button reset timer every second
void neither_button () {
  while (!SYSTEM_input() & !PED_input()) {
    if ((GPTMRIS_TIMER0 & 0x1) == 1) { // 1 second pass
      GPTMICR_TIMER0 = 0x1;
      break;
    }
  }
}

//initialize timer 0A
void timer_init (void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; //enable timer bit
  delay++;
  delay++;
  
  GPTMCTL_TIMER0 &= 0x00; //disable timer
  GPTMCFG_TIMER0 &= 0x00; //32 bit mode
  GPTMTAMR_TIMER0 |= 0x02; //periodic timer and countdown mode
  GPTMTAILR_TIMER0 = 0xF42400; //1Hz
  GPTMCTL_TIMER0 |= 0x01; //enable timer
}


// Traffic_light sets up the FSM modeTL for the states of traffic light
void Traffic_Light()
{  
  // set up state transitions for FSM
  switch(TL_State) 
  {
  // case for start position
  case TL_SMStart:
    TL_State = TL_off;
    break;
  
  // case for stop state
  case TL_stop:
    TL_State = TL_go;
    count = 0;
    for (int i = 0; i < 5; i++) { // 5 second pass
      GPTMICR_TIMER0 |= 0x1;
      system_button_check();
      neither_button ();
    }
    break;
    
  // case for warn state
  case TL_warn:
    TL_State = TL_stop;
    count = 0;
    for (int i = 0; i < 5; i++) { // 5 second pass
      GPTMICR_TIMER0 |= 0x1;
      system_button_check();
      neither_button ();
    }
    break;

  // case for go state
  case TL_go:
    TL_State = TL_stop;
    count = 0;
    for (int i = 0; i < 5; i++) { // 5 second pass
      GPTMICR_TIMER0 |= 0x1;
      system_button_check();
      ped_button_check();
      neither_button ();
    }
    break;  
    
  // case for off state
  case TL_off:
    count = 0;
    for (int i = 0; i < 100; i++) { 
      GPTMICR_TIMER0 |= 0x1;
      while (SYSTEM_input()) { 
        if ((GPTMRIS_TIMER0 & 0x1) == 1) {  // 1 second  pass
          count++;
          GPTMICR_TIMER0 |= 0x1;
          if (count >= 2) { // 2 second pass 
            TL_State = TL_stop;
            GPTMICR_TIMER0 = 0x1;
            break;
          }
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

// Task 1b: use traffic light FSM with timer
void main (void) {
  TL_State = TL_SMStart;
  while(1) {
    Traffic_Light();
  }
}