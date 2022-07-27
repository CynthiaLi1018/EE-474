// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 2a
// 8/9/21

// This is the main function file for task 2a, majority of the code is from Lab2
// It will create two virtual buttons (sys and ped) on the LCD and detect a
// press that's longer than 2s. By default, the system is off, all three LEDs 
// are black. It will turn on the system to stop state if system button is
// pressed. It will repeat stop-go state pattern if no button is pressed, but if
// sys button is pressed, it will turn off the system, or if ped button is
// pressed, when it is in stop state, it will stay in current state, when it is
// in go state, it will proceed to warn state. The functionality is the same
// as Lab2 except it's now using LCD.

#include "task2a_inits.h"
#include "task2a.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include <stdio.h>
#include <stdint.h>

int time = 0;
int cnt = 0;
int prev = 0;

void GPTMInit()
{
  RCGCTIMER |= GPTM0_16_32; // Enable 16/32 Timer 0

  GPTMCTL_0 = GPTMA_DISABLE;      // Disable Timer A
  GPTMCFG_0 = TM_MODE_32;         // Select two timer to 32-bit mode
  GPTMTAMR_0 |= TAMR_PER_TM_MODE; // Set periodic timer mode
  GPTMTAMR_0 &= ~TACDIR_COUNT_UP; // Configure TACDIR0 to count down
  GPTMTAILR_0 = N16_MIL;          // Load value of 16 million into GPTMTAILR0
  GPTMCTL_0 |= GPTMA_ENABLE;      // Enable Timer A
}

int one_second()
{
  return (GPTMRIS_0 & 0x1);
}

void resetTimer()
{
  GPTMICR_0 |= 0x1;
}

void oneHertz(int n)
{
  resetTimer();
  int t = 0;
  while (t < n)
  {
    if (one_second())
    {
      t++;
      resetTimer();
    }
  }
}

void ADC0SS3_Handler(void)
{                           
  ADCISC |= 0x8;          // clear the ADC0 interrupt flag
}

void LCD_Pattern() {
  // set the LCD background color
  LCD_ColorFill(Color4[7]); // fill LCD with white color
  
  // craete the virtual buttons with labels on the LCD
  LCD_SetCursor(40, 200);
  LCD_DrawCircle(50, 200, 20, Color4[9]);
  LCD_Printf("PED");
  LCD_SetCursor(260, 200);
  LCD_DrawCircle(270, 200, 20, Color4[9]);
  LCD_Printf("SYS");
  
  // create 3 default (black) LEDs on the LCD
  off();
}

unsigned long sys_switch()
{
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  if (x + y < 2500)    // no press
  {
    return 0;
  }
  else    // there is a press
  {
    oneHertz(2);
    if (x + y >= 2500)    // longer than 2s press
    {
      return 1;
    }
    else    // less than 2s press
    {
      return 0;
    }
  }
  return 0;
}

unsigned long ped_switch()
{
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  if (!(x + y <= 2300 && (x + y) >= 1000))    // no press
  {
    return 0;
  }
  else    // there is a press
  {
    oneHertz(2);
    if (x + y <= 2300 && (x + y) >= 1000)    // press longer than 2s
    {
      return 1;
    }
    else    // press less than 2s
    {
      return 0;
    }
  }
  return 0;
}

void stop(void)
{
  LCD_DrawFilledCircle(170, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(276, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(53,  100, 20, Color4[12]);
}

void warn(void)
{
  LCD_DrawFilledCircle(53, 100,  20, Color4[0]);
  LCD_DrawFilledCircle(276, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(170, 100, 20, Color4[14]);
}

void go(void)
{
  LCD_DrawFilledCircle(53, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(170, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(276, 100, 20, Color4[10]);
}

void off(void)
{
  LCD_DrawFilledCircle(53, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(170, 100, 20, Color4[0]);
  LCD_DrawFilledCircle(276, 100, 20, Color4[0]);
}

// FSM state declaration
enum TL_States {TL_Start, TL_Go, TL_Warn, TL_Stop, TL_Off} TL_State; 

void TrafficLight()
{
  if (GPTMRIS_0 & 0x1)
  {
    cnt += 1;
    resetTimer();
  }
  // state transitions
  switch (TL_State)
  {
    case TL_Start:
      prev = cnt;
      TL_State = TL_Off;
      break;
    case TL_Go:
      if (sys_switch())
      {
        TL_State = TL_Off;
      }
      else if (ped_switch())
      {
        TL_State = TL_Warn;
        time = 0;
      }
      // default pattern when no press
      else if (cnt - prev >= 5)
      {
        prev = cnt;
        TL_State = TL_Stop;
      }
      else
      {
        time++;
      }
      break;
    case TL_Warn:
      if (sys_switch())
      {
        TL_State = TL_Off;
      }
      else if (cnt - prev >= 5)
      {
        prev = cnt;
        TL_State = TL_Stop;
      }
      else
      {
        time++;
      }
      break;
    case TL_Stop:
      if (sys_switch())
      {
        TL_State = TL_Off;
      }
      else if (ped_switch())
      {
        TL_State = TL_Stop;
        time = 0;
      }
      //default pattern when no press
      else if (cnt - prev >= 5)
      {
        prev = cnt;
        TL_State = TL_Go;
      }
      else
      {
        time++;
      }
      break;
    case TL_Off:
      time = 0;
      if (sys_switch())
      {
        TL_State = TL_Stop;
      }
      else
      {
        TL_State = TL_Off;
      }
      break;  

    default:
      TL_State = TL_Start;
      break;
  }
    // State actions        
  switch (TL_State) 
  {
    case TL_Go:
      go();
      break;
    case TL_Warn:
      warn();
      break;
    case TL_Stop:
      stop();
      break;
    case TL_Off:
      off();
      break;
    default:
      off();
      break;
  }
}

enum frequency freq = PRESET3; 

int main()
{
  LCD_Init(); // Initialize LCD
  Touch_Init();
  GPTMInit();
  PLL_Init(freq);           // Set system clock frequency to 60 MHz
  TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0

  // display the default LED and button pattern on the LCD
  LCD_Pattern();
  while (1)
  {
    TrafficLight();
  }
  return 0;
}