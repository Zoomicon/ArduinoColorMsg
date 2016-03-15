/*
 * Serial output functions
 * 
 * Components:
 *   Aduino board
 * 
 * Wiring:
 *   Connect Arduino board (e.g. via USB cable) to PC
 * 
 * After the program is uploaded and running, can see the serial output (Arduino USB connection provides a virtual serial port) at Arduino IDEs Serial Monitor window
 */

#include <Streaming.h> //http://arduiniana.org/libraries/streaming/

#define SPACE ' '

/*
 * Initialization
 */
void init_serial() {
 Serial.begin(9600);
}

/*
 * Show string and clear after a delay
 */
void show_message_serial(char* msg) {
  Serial << endl << msg << endl << "" << endl; //can't use << endl << endl to print a blank line, use endl << "" << endl instead
}

/*
 * Show R,G,B color values at serial output
 */
void show_color_serial(uint16_t red, uint16_t green, uint16_t blue) {
  Serial << red << SPACE << green << SPACE << blue << endl;
}

/*
 * Show Red / Green / Blue color element names at serial output
 */
void show_color_name_serial(bool isRed, bool isGreen, bool isBlue) {
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
