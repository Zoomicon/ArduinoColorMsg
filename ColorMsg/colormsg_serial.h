#include <Streaming.h> //http://arduiniana.org/libraries/streaming/

#define SPACE " "

void init_serial(){
 Serial.begin(9600);
 Serial << "ColorMsg 1.0" << endl;
}

void show_color_serial(uint16_t red, uint16_t green, uint16_t blue){
  Serial << red << SPACE << green << SPACE << blue << endl;
}

