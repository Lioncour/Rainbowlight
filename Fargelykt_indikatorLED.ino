#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define pin 9         // Neopixel pin
#define pickBtn 7     // plukkeknapp pin
#define lightBtn 4    // tømmeknapp pin

#define numPixels 5   // antall LEDs

uint32_t clearLimit;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, pin, NEO_RGB + NEO_KHZ800);

bool pickBtnState = 1;
bool pickPreState = 1;

bool lightBtnState = 1;

uint32_t white = strip.Color(255, 255, 255);
uint32_t color;

bool debug = 0;

void setup() {
  pinMode(pickBtn, INPUT_PULLUP);
  pinMode(lightBtn, INPUT_PULLUP);
  
  //strip.setBrightness(brightness);
  strip.begin();
  strip.show();
  if (debug) Serial.begin(9600);

  // start kalibrering
  
  while (millis() < 1000) {
    //getClear();
    if (getClear() > clearLimit) clearLimit = getClear();
  }
  clearLimit += 100;

  // kalibrering ferdig, blink tre ganger for bekreftelse

  for (uint8_t j = 0; j < 3; j++) {
    for (uint8_t i = 0; i < numPixels; i++) strip.setPixelColor(i, white);
    strip.show();
    delay(50);
    for (uint8_t i = 0; i < numPixels; i++) strip.setPixelColor(i, 0);
    strip.show();
    delay(50);
  }

  // sensor klar
  
}

void loop() {
  pickBtnState = digitalRead(pickBtn);
  lightBtnState = digitalRead(lightBtn);

  if (pickBtnState != pickPreState) {
    if (!pickBtnState) pick();
    pickPreState = pickBtnState;
  }
  
  if (!lightBtnState) lightUp();
  else turnOff();

}
