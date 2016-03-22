/*
 * ColorMsg 2.0
 * 
 * Read a series of emitted color values (Red, Green or Blue) and decode letters to display a message
 * Also displays Red, Green and Blue elements of received colors (via LED, LCD, Serial and Buzzer)
 * 
 * Components:
 *   Arduino board
 *   See source code for the individual modules
 */
 
#include "serial.h"
#include "leds.h"
#include "lcd.h"
#include "speaker.h"
#include "colorsensor.h"
#include "decoding.h"

#define scale 1
#define threshold_red 240
#define threshold_green 220
#define threshold_blue 240

/*
 * Initialization
 */
void setup() {
  init_serial();
  init_leds();
  init_lcd(); //shows program name and version at 1st LCD row
  init_speaker();
  init_colorsensor();

  show_message_serial("ColorMsg 2.0");
  show_message_lcd("ColorMsg 2.0", 2000); //show version for 2sec (2000msec)
  play(melody0, melody0_length);
}

/*
 * Main loop
 */
void loop() {
  uint16_t red, green, blue;
  read_color(false, &red, &green, &blue, scale); //read color from color sensor
  //read_color_random(&red, &green, &blue, threshold_red, threshold_green, threshold_blue); //get a random color value
  //read_color_random_pure(&red, &green, &blue, threshold_red, threshold_green, threshold_blue); //get a random color value (pure Red or Green or Blue only)

  bool isRed, isGreen, isBlue;
  find_color(&isRed, &isGreen, &isBlue, red, green, blue, threshold_red, threshold_green, threshold_blue);

  show_color_leds(isRed, isGreen, isBlue);

  show_color_serial(red, green, blue);
  show_color_name_serial(isRed, isGreen, isBlue);

  //show_color_lcd(0, red, green, blue); //print color element values to given LCD row
  show_color_name_lcd(0, isRed, isGreen, isBlue); //print color name (for each detected color element) to given LCD row
  //
  print_char_lcd(1, decode_color_name(isRed, isGreen, isBlue)); //print detected characters (if any) to given LCD row

  show_color_name_speaker(isRed, isGreen, isBlue); 
}
