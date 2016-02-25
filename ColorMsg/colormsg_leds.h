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

void show_color_leds(uint16_t red, uint16_t green, uint16_t blue, uint16_t threshold_red, uint16_t threshold_green, uint16_t threshold_blue){
  digitalWrite(pin_red, (red > threshold_red)? HIGH:LOW);  
  digitalWrite(pin_green, (green > threshold_green)? HIGH:LOW);  
  digitalWrite(pin_blue, (blue > threshold_blue)? HIGH:LOW); 
}

