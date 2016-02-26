/*
 * Prints to serial output the supplied color RGB value and color component (red, green, blue) names whose value is above given thresholds
 */

#include <Streaming.h> //http://arduiniana.org/libraries/streaming/

#define SPACE " "

void init_serial(){
 Serial.begin(9600);
 Serial << endl << "" << endl << "ColorMsg 1.0" << endl << "" << endl; //can't use << endl << endl to print a blank line, use endl << "" << endl instead
}

void show_color_serial(uint16_t red, uint16_t green, uint16_t blue){
  Serial << red << SPACE << green << SPACE << blue << endl;
}

void show_color_name_serial(bool isRed, bool isGreen, bool isBlue){
  bool foundColor = false;
  
  if (isRed) {
    Serial << " red";
    foundColor = true;
  }
  
  if (isGreen) {
    Serial << " green";
    foundColor = true;
  }
  
  if (isBlue) {
    Serial << " blue";
    foundColor = true;
  }

  if (foundColor)
    Serial << endl;
}
