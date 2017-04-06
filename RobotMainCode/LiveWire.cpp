
#include <Arduino.h>
#include "GlobalDefines.h"
#include "LiveWire.h"

void liveWireInit()
{
  pinMode(LIVEWIRE, INPUT);
  
  pinMode(INDICATOR, OUTPUT);
  digitalWrite(INDICATOR, LOW);
}

void toggleIndicator()
{
    for(int i = 0; i < BLINK_COUNT; i++)
    {
       digitalWrite(INDICATOR, HIGH);
       delay(500);
       digitalWrite(INDICATOR, LOW);
       delay(500);
    }
}

bool isOT()
{
  int pulse = 0;
  int rawPulse = 0;
  
  for(int i = 0; i < SAMP_COUNT; i++ )
  {
    rawPulse = pulseIn(LIVEWIRE, HIGH, TIMEOUT*1000);
    pulse = abs(pulse)+abs(rawPulse);
  }

  pulse = pulse/SAMP_COUNT;
  
  if(ENABLE_LOG_LIVEWIRE)
  {
    Serial.print("\nLive Wire Pulse Width: ");
    Serial.print(pulse);
    Serial.println("us");
  }
  
  if(abs(pulse) > MIN_THRESH && abs(pulse) < MAX_THRESH)
  {
    //toggleIndicator();
    return true;
  }
  else
  {
    return false;
  }
}


