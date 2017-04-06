
 #include <Arduino.h>
 #include "GlobalDefines.h"
 #include "Motors.h"
 #include "Ultrasonic.h"

void motorInit()
{
  pinMode(stepPin,OUTPUT);
  digitalWrite(stepPin,LOW);

  pinMode(FL_dir,OUTPUT);
  digitalWrite(FL_dir,HIGH);

  pinMode(FR_dir,OUTPUT);
  digitalWrite(FR_dir,LOW);

  pinMode(BL_dir,OUTPUT);
  digitalWrite(BL_dir,HIGH);

  pinMode(BR_dir,OUTPUT);
  digitalWrite(BR_dir,LOW);
}

void go(float steps)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\ngo()");
		Serial.print("New motor setpoint:\t");
		Serial.println(steps, DEC);
	}

	for(unsigned long i = 0; i < steps; i++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(step_delay);
	}
}

void forward(float in)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\nforward()");
	}

	digitalWrite(FL_dir, HIGH);
	digitalWrite(FR_dir, LOW);
	digitalWrite(BL_dir, HIGH);
	digitalWrite(BR_dir, LOW);
  
	go(in*in_sp_vert);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nMoved Forward\t");
		Serial.print(in);
		Serial.println("in");
	}
}

void backward(float in)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\nbackward()");
	}

	digitalWrite(FL_dir, LOW);
	digitalWrite(FR_dir, HIGH);
	digitalWrite(BL_dir, LOW);
	digitalWrite(BR_dir, HIGH);

	go(in*in_sp_vert);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nMoved Backward\t");
		Serial.print(in);
		Serial.println("in");
	}
}

void right(float in)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\nright()");
	}

	digitalWrite(FL_dir, HIGH);
	digitalWrite(FR_dir, HIGH);
	digitalWrite(BL_dir, LOW);
	digitalWrite(BR_dir, LOW);

	go(in*in_sp_lat);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nMoved Right\t");
		Serial.print(in);
		Serial.println("in");
	}
}



void left(float in)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\nleft()");
	}

	digitalWrite(FL_dir, LOW);
	digitalWrite(FR_dir, LOW);
	digitalWrite(BL_dir, HIGH);
	digitalWrite(BR_dir, HIGH);

	go(in*in_sp_lat);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nMoved Left\t");
		Serial.print(in);
		Serial.println("in");
	}
}

void cw(float deg)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\ncw()");
	}

	digitalWrite(FL_dir, HIGH);
	digitalWrite(FR_dir, HIGH);
	digitalWrite(BL_dir, HIGH);
	digitalWrite(BR_dir, HIGH);
  
	go(deg*deg_sp);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nRotated Clockwise\t");
		Serial.print(deg);
		Serial.println("deg");
	}
}

void ccw(float deg)
{
	if(ENABLE_LOG_MOTORS)
	{
		Serial.println("\nccw()");
	}

	digitalWrite(FL_dir, LOW);
	digitalWrite(FR_dir, LOW);
	digitalWrite(BL_dir, LOW);
	digitalWrite(BR_dir, LOW);

	go(deg*deg_sp);

	if(ENABLE_LOG_MOTORS)
	{
		Serial.print("\nRotated Counter-Clockwise\t");
		Serial.print(deg);
		Serial.println("deg");
	}
}
