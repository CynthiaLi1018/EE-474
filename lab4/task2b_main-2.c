// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 2a
// 8/10/21

// This is the main function file for task 2b, majority of the code is provided.
// The code is implemented following the comment guide.
// It will create two virtual buttons (sys and ped) on the LCD and detect a
// press that's longer than 2s. By default, the system is off, all three LEDs 
// are black. It will turn on the system to stop state if system button is
// pressed. It will repeat stop-go state pattern if no button is pressed, but if
// sys button is pressed, it will turn off the system, or if ped button is
// pressed, when it is in stop state, it will stay in current state, when it is
// in go state, it will proceed to warn state. The functionality is the same
// as Lab2 except it's now using LCD.

#include "FreeRTOS.h"
#include "task.h"

#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "task2b_inits.h"
#include "task2b.h"
#include "PLL_Header.h"

// global variables
int pedestrian_status = 0;
int onoff_status = 0;

// Define states in FSM
enum state {OFF, GO, WARN, STOP, INIT} state;

// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);

// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}

// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  // Moreover, initialize the PLL to set the system clock to 60 MHz.
  LCD_Init(); // Initialize LCD
  Touch_Init();
  PLL_Init(PRESET2);
  LCD_Pattern();
  
  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower. It is possible to assign
  // the same priority to all the tasks, however.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, 2, NULL);
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 1, NULL);
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 0, NULL);

  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what the terminology preemptive and
  // non-preemptive mean.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
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
  if (x + y >= 2500)    // press
  {
    return 1;
  }
  else    // no press
  {
    return 0;
  }
}

unsigned long ped_switch()
{
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  if (x + y <= 2300 && (x + y) >= 1000)    // press
  {
    return 1;
  }
  else    // no press
  {
    return 0;
  }
}

void StartStop(void *p) {
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 3
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();

    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if (sys_switch()) { // replace this condition checking with something else
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        // Set the global flag
        onoff_status = 1;
        // Clear the timer
        prev_onoff_tick_time = curr_onoff_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      prev_onoff_tick_time = curr_onoff_tick_time;
    }

    vTaskDelay(1);
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;

  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  //
  // (Refer to instructions in the StartStop function to implement
  // this function.)
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();
    if (ped_switch())
    {
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000)
      {                                          // switch pressed for 2 seconds
        pedestrian_status = 1;                   // Set the global flag
        prev_ped_tick_time = curr_ped_tick_time; // Clear the timer
      }
      else
      {
        pedestrian_status = 0; // Clear the global flag
      }
    }
    else
    {
      pedestrian_status = 0;                   // Clear the global flag
      prev_ped_tick_time = curr_ped_tick_time; // Clear the timer
    }

    vTaskDelay(1);
  }
}

void Control(void *p) {
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();

    // If the one of the virtual lights been lighting up for 5 or more
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick.
    if (curr_light_tick_time - prev_light_tick_time >= 5000 || state == INIT ||
        onoff_status || pedestrian_status)
    {
      prev_light_tick_time = curr_light_tick_time; // Reset the light tick
      if (state == INIT) {
        state = STOP; // Switch to next state
      }
      
      // FSM state transitions
      switch (state)
      {
      case OFF:
        if (onoff_status)
          state = STOP;
        break;
      case GO:
        if (onoff_status)
          state = OFF;
        else if (pedestrian_status)
          state = WARN;
        else
          state = STOP;
        break;
      case WARN:
        if (onoff_status)
          state = OFF;
        else
          state = STOP;
        break;
      case STOP:
        if (onoff_status)
          state = OFF;
        else if (pedestrian_status)
          state = STOP;
        else
          state = GO;
        break;
      default:
         state = OFF;
        break;
      }
      FSM(); // Call FSM to change Light
    }
      
    vTaskDelay(1);
  }
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

void FSM(void) {
  // STEP 6
  //
  // Add your FSM implementation here.
  // This function will be called by the control task function.
  switch (state)
  {
  case OFF:
    off();
    break;
  case GO:
    go();
    break;
  case WARN:
    warn();
    break;
  case STOP:
    stop();
    break;
  default:
    off();
    break;
  }
}