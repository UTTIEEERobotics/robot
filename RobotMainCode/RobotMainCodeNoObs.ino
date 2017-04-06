#include <Adafruit_NeoPixel.h>
#include "Utils.h"
#include <Servo.h>

boolean exitVal = false;

int pinState;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  if(ENABLE_LOG_MAIN)
  {
      Serial.println("\n---------------------------------------------------------------------------");
      Serial.println("Start Log");
      Serial.println("---------------------------------------------------------------------------");
  }

  pinMode(12, INPUT);
  digitalWrite(12, LOW);

  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);

  utilInit();
  
  delay(10000);

  lightReady();

  do 
  {
	 pinState = digitalRead(12);
	 delay(500);
	 Serial.println(pinState);
  }while(pinState == LOW);

  forward(0.1);
  ccw(0.1);
  backward(0.1);
  cw(0.1);
}

void loop() 
{
    while(!exitVal)
    {
		for(int i = 0; i < FIELD_SIZE; i++)
		{
			if(!isLastCell())
			{
				nextCell();
				delay(100);

				digitalWrite(33, HIGH);
				delayMicroseconds(100);
				digitalWrite(33, LOW);

				checkForOT();
			}
		}
        
		lightMatrix();
		moveToCache();
		if(getCurrCellIndex() != 0)
		{
			cameraLedOn();
			delay(1500);
			Serial2.flush();
			startPi();
		}
		exitVal = true;
    }
}


