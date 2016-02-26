/*
 * Prints to 16x2 LCD display the supplied color RGB value and color component (red, green, blue) names whose value is above given thresholds
 * 
 * The circuit:
 * - LCD RS pin to digital pin 12
 * - LCD Enable pin to digital pin 11
 * - LCD D4 pin to digital pin 5
 * - LCD D5 pin to digital pin 4
 * - LCD D6 pin to digital pin 3
 * - LCD D7 pin to digital pin 2
 * - LCD R/W pin to ground
 * - LCD VSS pin to ground
 * - LCD VCC pin to 5V
 * - 10K resistor:
 * - ends to +5V and GND
 * - wiper to LCD VO pin (pin 3)
 * 
 * based on http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#include <LiquidCrystal.h> //https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Streaming.h> //http://arduiniana.org/libraries/streaming/

#define SPACE " "
#define SPACE16 "                "

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void init_lcd(){
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.noAutoscroll();
  lcd << "ColorMsg 1.0"; // Print a message to the LCD
  delay(2000); //show title for 2 sec
}

void clear_lcd_row(int row){
  lcd.setCursor(row, 0);
  lcd << SPACE16;
}

void show_color_lcd(uint16_t red, uint16_t green, uint16_t blue){
  lcd.setCursor(0, 1);
  lcd << red << SPACE
      << green << SPACE
      << blue << SPACE16; //clean any leftover text from previous color display step (e.g. if values were three-digit ones and now are two-digit ones) at the end (assuming autoscroll isn't on)
}

void show_color_name_lcd(bool isRed, bool isGreen, bool isBlue){
  lcd.setCursor(0, 0);
  lcd << SPACE16; //clear first row

  lcd.setCursor(0,0);
  if (isRed)
    lcd << " red";
  if (isGreen)
    lcd << " green";
  if (isBlue)
    lcd << " blue";
}

void print_char_lcd(char c){
  if (c != 0) {
    lcd.setCursor(0,0);
    lcd << SPACE16;
    
    lcd.setCursor(0,0);
    lcd << (int)c;

    lcd << ' ';

    lcd << ((c != 0)? c : ' ');
  }
}

