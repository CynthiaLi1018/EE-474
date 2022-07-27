// Cynthia Li
// 1839952
// EE 474 Lab 4 Task 1
// 08/03/21

// This is the file for main function of Task 1a.
// It should fill the LCD screen with different color.
// The desired color can be selected by changing the index of Color4 in the
// LCD_ColorFill() function.

#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"

int main() {
  LCD_Init();
  LCD_ColorFill(Color4[9]);  // fill the screen with bright blue
  return 0;
}