// 
// 
// 
#include "Grabber.h"
#include <Servo.h>

Servo myservo;
int pos = UP_POS;

void grabberInit()
{
	myservo.attach(SERVO_PIN);
	myservo.write(pos);
}

void up(){
	for (pos = DOWN_POS; pos <= UP_POS; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
}

void down(){
	for (pos = UP_POS; pos >= DOWN_POS; pos -= 1) { // goes from 180 degrees to 0 degrees
		myservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
}

void liftCacheLid()
{
	down();
	delay(2000);
	up();
}