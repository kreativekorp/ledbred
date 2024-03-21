#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "digitalWriteFast.h"
#include "config.h"
#include "pen.h"

void penBegin() {
  pinMode(PEN_PIN, INPUT_PULLUP);
}

int penDetect(Adafruit_NeoPixel & canvas) {
  int pen = 0;
  int n = canvas.numPixels();
  for (int m = 1; m < n; m <<= 1) {
    for (int i = 0; i < n; i++) {
      canvas.setPixelColor(i, (i & m) ? SENSE_LEVELS : 0);
    }
    canvas.show();
    delay(SENSE_DURATION);
    int set = analogRead(SENSE_PIN) SENSE_THRESHOLD;
    for (int i = 0; i < n; i++) {
      canvas.setPixelColor(i, (i & m) ? 0 : SENSE_LEVELS);
    }
    canvas.show();
    delay(SENSE_DURATION);
    int clr = analogRead(SENSE_PIN) SENSE_THRESHOLD;
    if (set == clr) {
      pen = -1;
      break;
    } else if (set) {
      pen |= m;
    }
  }
  canvas.clear();
  canvas.show();
  return pen;
}

int penReadSwitch() {
  return !digitalRead(PEN_PIN);
}

void penDebounce() {
  delay(PEN_DEBOUNCE);
  while (!digitalRead(PEN_PIN));
  delay(PEN_DEBOUNCE);
}
