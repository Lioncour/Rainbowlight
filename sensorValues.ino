#include "Adafruit_TCS34725.h"

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


uint16_t getClear() {

  uint16_t red, grn, blu, clear;
  tcs.setInterrupt(false); // turn on LED

  delay(50); // takes 50ms to read

  tcs.getRawData(&red, &grn, &blu, &clear);
  tcs.setInterrupt(true); // turn off LED

  uint32_t sum = clear;

  return clear;
}

void getColor() {
  uint16_t red, grn, blu, clear;
  tcs.setInterrupt(false); // turn on LED

  for (uint16_t i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x;
  }

  
  delay(50); // takes 50ms to read

  tcs.getRawData(&red, &grn, &blu, &clear);
  tcs.setInterrupt(true); // turn off LED

  uint32_t sum = red;
  sum += grn;
  sum += blu;
  sum = clear;

  float r, g, b;
  r = red; r /= sum;
  g = grn; g /= sum;
  b = blu; b /= sum;
  r *= 256; g *= 256; b *= 256;

  color = strip.Color(gammatable[(uint8_t)r], gammatable[(uint8_t)g], gammatable[(uint8_t)b]);
}
