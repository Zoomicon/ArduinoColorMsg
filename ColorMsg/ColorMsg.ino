/*
 * ColorMsg 2.0
 * 
 * Components:
 *   Arduino board
 *   See source code for the individual modules
 */
 
#include "colormsg_serial.h"
#include "colormsg_leds.h"
#include "colormsg_lcd.h"
#include "colormsg_speaker.h"
#include "colormsg_colorsensor.h"
#include "colormsg_decoding.h"

#define scale 1
#define threshold_red 180
#define threshold_green 300
#define threshold_blue 200

/*
 * Initialization
 */
void setup() {
  init_serial();
  init_leds();
  init_lcd(); //shows program name and version at 1st LCD row
  init_speaker();
  init_colorsensor();

  show_message_lcd("ColorMsg 2.0", 2000); //show version for 2sec (2000msec)
  play(melody0, melody0_length);
}

/*
 * Main loop
 */
void loop() {
  uint16_t red, green, blue;
  read_color(false, &red, &green, &blue, scale);
  //read_color_random(&red, &green, &blue, threshold_red, threshold_green, threshold_blue);

  bool isRed, isGreen, isBlue;
  find_color(&isRed, &isGreen, &isBlue, red, green, blue, threshold_red, threshold_green, threshold_blue);

  show_color_leds(isRed, isGreen, isBlue);

  show_color_serial(red, green, blue);
  show_color_name_serial(isRed, isGreen, isBlue);

  show_color_lcd(red, green, blue);
  //show_color_name_lcd(isRed, isGreen, isBlue);
  print_char_lcd(decode_color_name(isRed, isGreen, isBlue));

  show_color_name_speaker(isRed, isGreen, isBlue); 
}
