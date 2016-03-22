/*
 * LED on/off functions
 * 
 * Components:
 *   Arduino board
 *   Red, Green, Blue LEDs
 *   3 (three) 220 Ohm resistors
 * 
 * Wiring:
 *   Red LED + pole: pin 9
 *   Green LED + pole: pin 8
 *   Blue LED + pole: pin 7
 *   each LED's - pole: via resistor (separate ones) to GND
 * 
 * Based on:
 *   https://www.arduino.cc/en/Tutorial/Blink
 */

#define pin_red 9
#define pin_green 8
#define pin_blue 7

/*
 * Initialization
 */
void init_leds() {
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);
}

/*
 * Light up Red, Green, Blue LEDs
 */
void show_color_leds(bool isRed, bool isGreen, bool isBlue) {
  digitalWrite(pin_red, (isRed)? HIGH:LOW);  
  digitalWrite(pin_green, (isGreen)? HIGH:LOW);  
  digitalWrite(pin_blue, (isBlue)? HIGH:LOW); 
}

