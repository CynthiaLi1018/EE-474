// _________ MAIN PROGRAM_________

/* 
* Cynthia Li
* 1839952 
* 7/3/2021 
* The program allows two internal user input, SW1 to control LED1, SW2 to 
* control LED2. When button is pressed, LED should lit, otherwise it it be
* turned off. */

#include <stdint.h> 
#include "task_2.h"

const int SYSTEM = 0x01;      // pin 0
const int PEDESTRIAN = 0x02;  // pin 1
const int RED = 0x04;         // pin 2
const int YELLOW = 0x40;      // pin 6
const int GREEN = 0x80;       // pin 7

// LED_init sets up the access for the LED connected to Pin PM2, 6, 7
void LED_init (void) 
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x800 ; // activate clock for Port M
  delay++;
  delay++;
  
  // set up the red LED
  GPIOAMSEL_M &= ~RED ; 
  GPIODIR_M |= RED; 
  GPIOAFSEL_M &= ~RED;
  GPIODEN_M |= RED;
  
  // set up the yellow LED
  GPIOAMSEL_M &= ~YELLOW; 
  GPIODIR_M |= YELLOW; 
  GPIOAFSEL_M &= ~YELLOW;
  GPIODEN_M |= YELLOW;
 
  // set up the green LED
  GPIOAMSEL_M &= ~GREEN; 
  GPIODIR_M |= GREEN; 
  GPIOAFSEL_M &= ~GREEN;
  GPIODEN_M |= GREEN;
}

// red_on turns on the red LED connected to PM2
void red_on (void)
{
  GPIODATA_M |= RED;
}

// red_off turn off the red LED connected to PM2
void red_off (void)
{
  GPIODATA_M &= ~RED;
}

// yellow_on turn on the red LED connected to PM6
void yellow_on (void)
{
  GPIODATA_M |= YELLOW;
}

// yellow_off turn off the red LED connected to PM6
void yellow_off (void)
{
  GPIODATA_M &= ~YELLOW;
}

// green_on turn on the green LED connected to PM7
void green_on (void)
{
  GPIODATA_M |= GREEN;
}

// green_off turn off the green LED connected to PM7
void green_off (void)
{
  GPIODATA_M &= ~GREEN;
}

// extern_switch_init sets up the access for the switches connected to PM0, PM1
void extern_switch_init (void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x800; // Enable Port N Gating Clock
  delay++;
  delay++;
  
  // set up system button connected to PM0
  GPIOAMSEL_M &= ~SYSTEM;    // Disable PM0 analog function
  GPIOAFSEL_M &= ~SYSTEM;    // Select PM0 regular port function
  GPIODIR_M &= ~SYSTEM;    // Set PM0 to input direction
  GPIODEN_M |= SYSTEM;    // Enable PM0 digital function
  
  // set up pedestrian button connected to PM1
  GPIOAMSEL_M &= ~PEDESTRIAN;    // Disable PM1 analog function
  GPIOAFSEL_M &= ~PEDESTRIAN;    // Select PM1 regular port function
  GPIODIR_M &= ~PEDESTRIAN;    // Set PM1 to input direction
  GPIODEN_M |= PEDESTRIAN;    // Enable PM digital function
}

// system_input returns status of system button: pressed or not
unsigned long system_input (void)
{
  return (GPIODATA_M & SYSTEM); // 0x1 (pressed) or 0 (not pressed)
}

// pedestrian_input returns status of pedestrian button: pressed or not
unsigned long pedestrian_input (void)
{
  return (GPIODATA_M & PEDESTRIAN); // 0x2 (pressed) or 0 (not pressed)
}

// define states of the FSM
enum TL_States {TL_SMStart, TL_stop, TL_warn, TL_go, TL_off} TL_State;

/* trafficLight set up the FSM for traffic light model and has the following 
* functionality:
* The system is on by default;
* when the system button is pressed, all LED lights are turned off;
* when the system is off and the system button is pressed, the system is turned
* on again, the LED would repeat a red_on - red_off - green_on - green_off
* pattern periodically if pedestrian button is not pressed;
* when the system is on, and the pedestrian button is pressed when the red LED
* is on, the red LED stays as lit up and other lights are off; 
* when the system is on, and the pedestrian button is pressed when the green 
* LED is on, the green light turns off, the yellow LED turns on, last for a 
* short time and turns off, and the red LED turns on. */
void trafficLight ()
{
  // FSM state transitions
  switch(TL_State) {
    // initialize start position to be the stop state
    case TL_SMStart:
      TL_State = TL_stop;
    
    // stop state transitions
    case TL_stop:
      for (int j = 0; j < 500000; j++) {
        if (system_input())
        {
          TL_State = TL_off; 
          break;
        }
        if (pedestrian_input())
        {
          TL_State = TL_stop;
        }
        else
        {
          TL_State = TL_go;
        }
      }
      break;
    
    // warn state transitions
    case TL_warn:
     for (int j = 0; j < 500000; j++) {
        if (system_input())
        {
          TL_State = TL_off; 
          break;
        }
        TL_State = TL_stop;
      }
      break;
    
    // go state transitions
    case TL_go:
      for (int j = 0; j < 500000; j++) {
        if (system_input())
        {
          TL_State = TL_off; 
        }
        else if (pedestrian_input())
        {
          TL_State = TL_warn;
        }
        else
        {
          TL_State = TL_stop;
        }
      }
      break;
    
    // off state transitions
    case TL_off:
      TL_State = TL_off;
      for(int i = 0; i < 500000; i++) 
      {
        if (system_input()) {
          TL_State = TL_stop;
          break;
        }
      }
      break;
  }
  
  // FSM state actions
  switch (TL_State) {
    case TL_stop:
      red_on();
      yellow_off();
      green_off();
      break;
    case TL_warn:
      red_off();
      yellow_on();
      green_off();
      break;
    case TL_go:
      red_off();
      yellow_off();
      green_on();
      break;
    case TL_off:
      red_off();
      yellow_off();
      green_off();
      break;
  }
}

int main (void)
{
  // set up switches
  extern_switch_init();
  system_input();
  pedestrian_input();
  
  // set up LEDs
  LED_init();
  red_off();
  yellow_off();
  green_off();
  
  // initialize state for SM
  TL_State = TL_SMStart;
  
  while (1)
  {
    trafficLight();
  }
  
  return 1;
}