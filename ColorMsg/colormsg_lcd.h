/*
 * LCD display functions
 * 
 * Components:
 *   Arduino board 
 *   16x2 char LCD with HD44780 driver (e.g. http://grobotronics.com/lcd-module-16x2-5v-blue-white-el.html, probably https://www.adafruit.com/products/181 too)
 *   10K potentiometer (pot - variable resistor)
 * 
 * Wiring:
 *   LCD RS pin to digital pin 12
 *   LCD Enable pin to digital pin 11
 *   LCD D4 pin to digital pin 5
 *   LCD D5 pin to digital pin 4
 *   LCD D6 pin to digital pin 3
 *   LCD D7 pin to digital pin 2
 *   LCD R/W pin to ground
 *   LCD VSS pin to ground
 *   LCD VCC pin to 5V
 *   Potentiometer ends to +5V and GND
 *   Potentiometer wiper (output) to LCD VO pin (pin 3)
 * 
 * Based on:
 *   http://www.arduino.cc/en/Tutorial/LiquidCrystal
 *   http://learning.grobotronics.com/2013/07/controlling-lcd-displays-with-the-hitachi-hd44780-driver/
 */

#include <LiquidCrystal.h> //https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Streaming.h> //http://arduiniana.org/libraries/streaming/

#define ESC 27
#define SPACE ' '
#define SPACE16 "                "

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*
 * Clear given LCD row (assuming 16 columns)
 */
void clear_lcd_row(int row) {
  lcd.setCursor(0, row);
  lcd << SPACE16;
}

/*
 * Initialization
 */
void init_lcd() {
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.noAutoscroll(); //disable scrolling
  lcd.clear(); //clear LCD and position cursor at upper-left
}

/*
 * Show string and clear after a delay
 */
void show_message_lcd(char* msg, int delay_msec) {
  lcd.clear(); //clear LCD and position cursor at upper-left
  lcd << msg; // Print message to the LCD
  
  delay(delay_msec); //show for given msec
  lcd.clear(); //clear LCD and position cursor at upper-left
}

/*
 * Show R,G,B color values at given LCD row
 */
void show_color_lcd(int row, uint16_t red, uint16_t green, uint16_t blue) {
  clear_lcd_row(row); //clear given row
  
  lcd.setCursor(0, row); //go to given row, 1st column
  lcd << SPACE
      << red << SPACE
      << green << SPACE
      << blue << SPACE16; //clean any leftover text from previous color display step (e.g. if values were three-digit ones and now are two-digit ones) at the end (assuming autoscroll isn't on)
}

/*
 * Show Red / Green / Blue color element names at given LCD row
 */
void show_color_name_lcd(int row, bool isRed, bool isGreen, bool isBlue) {
  clear_lcd_row(row); //clear given row
  
  lcd.setCursor(0, row);
  if (isRed)
    lcd << " red";
  if (isGreen)
    lcd << " green";
  if (isBlue)
    lcd << " blue";
}

int char_column = 0;

/*
 * Clear the screen if ESC (=27) is given, else print given character if non-zero
 */
void print_char_lcd(int row, char c) {
  if (c == ESC) {
    clear_lcd_row(row); //clear LCD row
    char_column = 0; //move back to 1st column
  }
  else if (c != 0) {
    lcd.setCursor(char_column, row); //got to char_column at 2nd row
    lcd << c;
    if (++char_column == 16) { //if 2nd row is full...
      clear_lcd_row(row); //clear LCD row
      char_column = 0; //move back to 1st column
    }
  }
}

