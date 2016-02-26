/*
 * Lights up Red, Green and Blue LEDs if supplied RGB color components exceed given thresholds
 * 
 * Red LED + : pin 9
 * Green LED + : pin 8
 * Blue LED + : pin 7
 * all LEDs - : via resistor to GND
 */

#define pin_red 9
#define pin_green 8
#define pin_blue 7

void init_leds(){
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);
}

void show_color_leds(bool isRed, bool isGreen, bool isBlue){
  digitalWrite(pin_red, (isRed)? HIGH:LOW);  
  digitalWrite(pin_green, (isGreen)? HIGH:LOW);  
  digitalWrite(pin_blue, (isBlue)? HIGH:LOW); 
}

