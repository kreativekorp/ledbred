#include <Arduino.h>
#include "digitalWriteFast.h"
#include "config.h"
#include "rotary.h"

static const int rotaryDir[] = {0,-1,+1,0,+1,0,0,-1,-1,0,0,+1,0,+1,-1,0};
static int rotaryPositionFine = 0;
static int rotaryPositionCoarse = 0;
static int rotaryLastPosition = 0;
static int rotaryLastState = 3;

static void rotaryISR() {
  int rotaryNextState = 0;
  if (digitalReadFast(ROTARY_CK_PIN)) rotaryNextState |= 1;
  if (digitalReadFast(ROTARY_DT_PIN)) rotaryNextState |= 2;
  rotaryPositionFine += rotaryDir[(rotaryLastState << 2) | rotaryNextState];
  if (rotaryNextState == 3) rotaryPositionCoarse = rotaryPositionFine >> 2;
  rotaryLastState = rotaryNextState;
}

void rotaryBegin() {
  pinMode(ROTARY_CK_PIN, INPUT_PULLUP);
  pinMode(ROTARY_DT_PIN, INPUT_PULLUP);
  pinMode(ROTARY_SW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROTARY_CK_PIN), rotaryISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_DT_PIN), rotaryISR, CHANGE);
}

int rotaryReadPosition() {
  return rotaryPositionCoarse;
}

int rotaryReadDirection() {
  int diff = rotaryPositionCoarse - rotaryLastPosition;
  rotaryLastPosition = rotaryPositionCoarse;
  return diff;
}

int rotaryReadSwitch() {
  return !digitalRead(ROTARY_SW_PIN);
}

void rotaryDebounce() {
  delay(ROTARY_DEBOUNCE);
  while (!digitalRead(ROTARY_SW_PIN));
  delay(ROTARY_DEBOUNCE);
}
