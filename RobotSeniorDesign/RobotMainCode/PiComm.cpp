

#include <Arduino.h>
#include "GlobalDefines.h"
#include "PiComm.h"
#include "Motors.h"
#include "CameraLed.h"
#include "Utils.h"

volatile PiState_t PiState;
volatile int x_pix;
volatile int y_pix;

void piCommInit()
{
	Serial2.begin(115200);

	pinMode(PiStartPin, OUTPUT);
	digitalWrite(PiStartPin, LOW);

	PiState = SLEEP;
	x_pix = 0;
	y_pix = 0;
}

void startPi()
{
	if(ENABLE_LOG_PICOMM)
	{
		Serial.println("\nstartpi()");
	}

	digitalWrite(PiStartPin, HIGH);
	delayMicroseconds(100);
	digitalWrite(PiStartPin, LOW);
}

void serialEvent2()
{
	if(ENABLE_LOG_PICOMM)
	{
		Serial.println("\nserialEvent2()");
	}

	while(Serial2.available())
	{
		char firstBite = Serial2.peek();

		if(ENABLE_LOG_PICOMM)
		{
			Serial.print("\nNew character from RasPi:\t");
			Serial.println(firstBite);
		}

		switch (PiState)
		{
		case SLEEP :
			if(ENABLE_LOG_PICOMM)
			{
				Serial.print("\nCurrent State:\t");
				Serial.println(PiState);
			}

			switch (firstBite)
			{
				case '#':
					Serial2.read();
					PiState = LID;
					if(ENABLE_LOG_PICOMM)
					{
						Serial.print("\nChanged State to:\t");
						Serial.println(PiState);
					}

				break;
				default:
					Serial.print("\nReceived from pi:\t");
					Serial.println(Serial2.read());
				break;
			}
			break;
		case LID :
			if(ENABLE_LOG_PICOMM)
			{
				Serial.print("\nCurrent State:\t");
				Serial.println(PiState);
			}
			
			switch (firstBite)
			{
				case '#':
					Serial2.read();
					PiState = DIE;
					delay(1000);
					if(getCurrCellIndex() != 0)
					{
						forward(5.3);
						liftCacheLid();
						delay(5000);
						backward(5.3);
					}
					delay(2000);
					cameraLedOn();
					delay(1500);
					startPi();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.print("\nChanged State to:\t");
						Serial.println(PiState);
					}

				break;
                
				case '?':
					Serial2.read();
					startPi();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.println("\nLid read failure restart pi:\t");
					}
				break;

				case '*':
					Serial2.read();
					x_pix = Serial2.parseInt();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.print("\nRecieved x pixel distance:\t");
						Serial.println(x_pix);
					}

					y_pix = Serial2.parseInt();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.print("\nRecieved y pixel distance:\t");
						Serial.println(y_pix);
					}

					if(x_pix >= 0)
					{
						right(x_pix*in_pix);
					}
					else
					{
						left(abs(x_pix)*in_pix);
					}

					delayMicroseconds(10000);
					if(y_pix >= 0)
					{
						backward(y_pix*in_pix);
					}
					else
					{
						forward(abs(y_pix)*in_pix);
					}

					startPi();
				break;
                
				default:
					Serial.print("\nReceived from pi:\t");
					Serial.println(Serial2.read());
				break;
			}
			break;
		case DIE :
			if(ENABLE_LOG_PICOMM)
			{
				Serial.print("\nCurrent State:\t");
				Serial.println(PiState);
			}

			switch (firstBite)
			{
				case '#':
					Serial2.read();
					PiState = SLEEP;

					cameraLedOff();
					moveToStart();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.print("\nChanged State to:\t");
						Serial.println(PiState);
					}
				break;

				case '?':
					Serial2.read();
					startPi();

					if(ENABLE_LOG_PICOMM)
					{
						Serial.println("\nDie read failure restart pi:\t");
					}
				break;
				default:
					Serial.print("\nReceived from pi:\t");
					Serial.println(Serial2.read());
				break;
			}
			break;
		default:
			Serial.print("\nReceived from pi:\t");
			Serial.println(Serial2.read());
		break;
        
		}
	}
}

