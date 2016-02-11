#include "colormsg_serial.h"
#include "colormsg_leds.h"
#include "colormsg_lcd.h"
#include "colormsg_speaker.h"
#include "colormsg_colorsensor.h"

#define scale 2
#define threshold 150

void setup() {
  init_serial();
  init_leds();
  init_lcd();
  init_speaker();
  init_colorsensor();
}

void loop() {
  uint16_t red, green, blue;
  read_color(false, &red, &green, &blue, scale);

  show_color_leds(red, green, blue, threshold);
  
  show_color_serial(red, green, blue);

  show_color_name_lcd(red, green, blue, threshold);
  show_color_lcd(red, green, blue);

  //play(melody1, melody1_length);
}
