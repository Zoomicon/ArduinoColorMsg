/*
 * Color sensor related functions
 *
 * Components:
 *   Arduino board
 *   Adafruit TCS34725 Color Sensor (https://learn.adafruit.com/adafruit-color-sensors/overview)
 * 
 * Wiring:
 *   Color Sensor connected to I2C serial bus via pins SDA (serial data) & SCL (serial clock)
 *   Assuming Pin 0 is disconnected and thus returns a "random" value
 * 
 * Based on:
 *   https://github.com/adafruit/Adafruit_TCS34725/blob/master/examples/colorview/colorview.ino
 */

#include <Wire.h> //https://www.arduino.cc/en/Reference/Wire //include required here only for older Arduino IDEs (https://github.com/adafruit/Adafruit_TCS34725/issues/10#issuecomment-182538818)
#include "Adafruit_TCS34725.h" //https://learn.adafruit.com/adafruit-color-sensors/program-it

Adafruit_TCS34725 tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //options: 1X, 4X, 16X, 60X

/*
 * Initialization
 */
void init_colorsensor() {
  tcs.begin();
  tcs.setInterrupt(true); //turn off ColorSensor's LED
  //tcs.clearInterrupt(); //probably not needed

  randomSeed(analogRead(0)); //assuming Pin 0 is disconnected
}

/*
 * Seleting whether to illuminate target or not, do read Red, Green, Blue color values and adjust them by given scale
 */
void read_color(bool illuminate, uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t scale) {     
  if (illuminate)
    tcs.setInterrupt(false); //turn on ColorSensor's LED
  
  delay(60);  // takes 50ms to read (delay 10 more)
  
  if (illuminate) 
    tcs.setInterrupt(true); //turn off ColorSensor's LED

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c); //read the raw sensor output for the Red, Green, Blue and Clear segments of the sensor

  //c = 1; //use to ignore clear because when using an optical fiber to transmit color, the user may touch it upon the sensor

  *red = map(r, 0, c * scale, 0, 255);
  *green = map(g, 0, c * scale, 0, 255);
  *blue = map(b, 0, c * scale, 0, 255);
}

/*
 * Return a random color value
 */
void read_color_random(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t red_threshold, uint16_t green_threshold, uint16_t blue_threshold) {
  *red = random(red_threshold * 2);
  *green = random(green_threshold * 2);
  *blue = random(blue_threshold * 2);
}

/*
 * Return a random color value (pure Red or Green or Blue only)
 */
void read_color_random_pure(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t red_threshold, uint16_t green_threshold, uint16_t blue_threshold) {
  // red = random value between 0 and (red_threshold*2 - 1)
  *red = random(red_threshold * 2);

  // if red>=red_threshold, set green=0 else green=random value between 0 and (green_threshold*2 - 1)
  *green = (*red >= red_threshold) ? 0 : random(green_threshold * 2);

  // if red>=red_threshold or green>=green_threshold, set blue=0 else blue=random value between 0 and (blue_threshold*2 - 1)
  *blue = ((*red >= red_threshold) || (*green >= green_threshold)) ? 0 : random(blue_threshold * 2);
}

/*
 * Check if given Red, Green, Blue values are above given thresholds
 */
void find_color(bool* isRed, bool* isGreen, bool* isBlue, uint16_t red, uint16_t green, uint16_t blue, uint16_t red_threshold, uint16_t green_threshold, uint16_t blue_threshold) {
  *isRed = (red > red_threshold);
  *isGreen = (green > green_threshold);
  *isBlue = (blue > blue_threshold);
}
