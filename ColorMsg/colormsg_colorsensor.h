//based on https://github.com/adafruit/Adafruit_TCS34725/blob/master/examples/colorview/colorview.ino

//Using Adafruit TCS34725 Color Sensor (https://learn.adafruit.com/adafruit-color-sensors/overview)
//connected to I2C serial bus via pins SDA (serial data) & SCL (serial clock)

#include <Wire.h> //https://www.arduino.cc/en/Reference/Wire //include required here only for older Arduino IDEs (https://github.com/adafruit/Adafruit_TCS34725/issues/10#issuecomment-182538818)
#include "Adafruit_TCS34725.h" //https://learn.adafruit.com/adafruit-color-sensors/program-it

Adafruit_TCS34725 tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //options: 1X, 4X, 16X, 60X

void init_colorsensor(){
  tcs.begin();
  tcs.setInterrupt(true); //turn off ColorSensor's LED
  //tcs.clearInterrupt(); //probably not needed
}

void read_color(bool illuminate, uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t scale){     
  if (illuminate)
    tcs.setInterrupt(false); //turn on ColorSensor's LED
  
  delay(60);  // takes 50ms to read (delay 10 more)
  
  if (illuminate) 
    tcs.setInterrupt(true); //turn off ColorSensor's LED

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c); //read the raw sensor output for the Red, Green, Blue and Clear segments of the sensor

  *red = map(r, 0, c * scale, 0, 255);
  *green = map(g, 0, c * scale, 0, 255);
  *blue = map(b, 0, c * scale, 0, 255);
}

