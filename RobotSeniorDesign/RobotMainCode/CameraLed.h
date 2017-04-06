// CameraLed.h

#ifndef _CAMERALED_h
#define _CAMERALED_h

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 4

#define DATA_PIN 52

void camereLedInit();
void cameraLedOn();
void cameraLedOff();


#endif

