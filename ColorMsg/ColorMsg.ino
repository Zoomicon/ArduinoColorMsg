#include "colormsg_serial.h"
#include "colormsg_leds.h"
#include "colormsg_lcd.h"
#include "colormsg_speaker.h"
#include "colormsg_colorsensor.h"

#define scale 1
#define threshold_red 180
#define threshold_green 150
#define threshold_blue 180

void setup() {
  init_serial();
  init_leds();
  init_lcd();
  init_speaker();
  init_colorsensor();
  play(melody0, melody0_length);  
}

void loop() {
  uint16_t red, green, blue;
  read_color(false, &red, &green, &blue, scale);

  show_color_leds(red, green, blue, threshold_red, threshold_green, threshold_blue);

  show_color_name_serial(red, green, blue, threshold_red, threshold_green, threshold_blue);
  show_color_serial(red, green, blue);

  show_color_name_lcd(red, green, blue, threshold_red, threshold_green, threshold_blue);
  show_color_lcd(red, green, blue);

  show_color_name_speaker(red, green, blue, threshold_red, threshold_green, threshold_blue);
}
