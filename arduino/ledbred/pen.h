#ifndef PEN_H
#define PEN_H

#include <Adafruit_NeoPixel.h>

void penBegin();
int penDetect(Adafruit_NeoPixel & canvas);
int penReadSwitch();
void penDebounce();

#endif
