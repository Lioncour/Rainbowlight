#define refreshRate 25

void pick() {
  if (debug) Serial.println("picking");
  getColor();

  strip.setPixelColor(numPixels-1, color);
  strip.show();
  
}

void lightUp() {
  if (debug) Serial.println("lighting up");
  
  for (uint8_t i = 0; i < numPixels - 1; i++) strip.setPixelColor(i, color);
  strip.show();
}

void turnOff() {
  if (debug) Serial.println("turning off");
  
  for (uint8_t i = 0; i < numPixels - 1; i++) strip.setPixelColor(i, 0);
  strip.show();
}
