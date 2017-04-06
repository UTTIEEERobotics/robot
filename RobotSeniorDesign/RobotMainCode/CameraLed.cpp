// 
// 
// 

#include "CameraLed.h"

CRGB leds[NUM_LEDS];


void camereLedInit()
{
	 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	 cameraLedOff();
}	

void cameraLedOn()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		//leds[i] = CRGB::White;
		leds[i].setRGB(128,128,128);
		FastLED.show();
		delay(50);
	}
}

void cameraLedOff()
{
	for( int i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(50);
	}
}