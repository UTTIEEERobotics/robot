/*
 * Functions for retrieving data from Ultrasonic sensors
 * 
 */

 #include <Arduino.h>
 #include "GlobalDefines.h"
 #include "Ultrasonic.h"
 #include "Motors.h"

 void ussInit()
{
    pinMode(FL_ECHO, INPUT);
    pinMode(FR_ECHO, INPUT);
    pinMode(R_ECHO, INPUT);
    pinMode(BR_ECHO, INPUT);
    pinMode(BL_ECHO, INPUT);
    pinMode(L_ECHO, INPUT);
    
    pinMode(FL_TRIG, OUTPUT);
    digitalWrite(FL_TRIG, LOW);
    pinMode(FR_TRIG, OUTPUT);
    digitalWrite(FR_TRIG, LOW);
    pinMode(R_TRIG, OUTPUT);
    digitalWrite(R_TRIG, LOW);
    pinMode(BR_TRIG, OUTPUT);
    digitalWrite(BR_TRIG, LOW);
    pinMode(BL_TRIG, OUTPUT);
    digitalWrite(BL_TRIG, LOW);
    pinMode(L_TRIG, OUTPUT);
    digitalWrite(L_TRIG, LOW);
}


/*
 * Used to get each sensor offset from front-edge of robot
 * Must set a detectable object at a distance specified by 
 * OFF_DIST from Ultrasonic.h in front of each sensor
 * Values can be copied and pasted into Ultrasonic.h from Serial Monitor
 */
void getOffsets()
{
    float count = 25;
    float offFL = 0;
    float offFR = 0;
    float offR = 0;
    float offBR = 0;
    float offBL = 0;
    float offL = 0;
    
    for(int i = 0; i < count; i++)
    {
        offFL += distFL();
    }
    offFL = (offFL/count) - OFF_DIST;
    
    for(int i = 0; i < count; i++)
    {
        offFR += distFR();
    }
    offFR = (offFR/count) - OFF_DIST;
    
    for(int i = 0; i < count; i++)
    {
        offBR += distBR();
    }
    offBR = (offBR/count) - OFF_DIST;
    
    for(int i = 0; i < count; i++)
    {
        offBL += distBL();
    }
    offBL = (offBL/count) - OFF_DIST;
    
    for(int i = 0; i < count; i++)
    {
        offL += distL();
    }
    offL = (offL/count) - OFF_DIST;
    
    for(int i = 0; i < count; i++)
    {
        offR += distR();
    }
    offR = (offR/count) - OFF_DIST;
    
    Serial.print("#define FL_OFF          ");
    Serial.print(offFL);
    Serial.println("       //Front-Left Offset from front edge of robot");
    Serial.print("#define FR_OFF          ");
    Serial.print(offFR);
    Serial.println("       //Front-Right Offset from front edge of robot");
    Serial.print("#define L_OFF          ");
    Serial.print(offR);
    Serial.println("       //Right Offset from front edge of robot");
    Serial.print("#define BR_OFF          ");
    Serial.print(offBR);
    Serial.println("       //Back-Right Offset from front edge of robot");
    Serial.print("#define BL_OFF          ");
    Serial.print(offBL);
    Serial.println("       //Back-Left Offset from front edge of robot");
    Serial.print("#define R_OFF          ");
    Serial.print(offL);
    Serial.println("       //Left Offset from front edge of robot");
}


 float distFL()
{ 
    float sum = 0;
    float avrg, dist;
    
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(FL_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(FL_TRIG, LOW);
        
        sum += pulseIn(FL_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;
    
    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - FL_OFF;
    
    if(ENABLE_LOG_USS)
    {
      Serial.print("\nFront-Left Dist:\t");
      Serial.println(dist);
    }
    
    return dist;
}


 float distFR()
{ 
    float sum = 0;
    float avrg, dist;

    //Take measurement samples
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(FR_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(FR_TRIG, LOW);
        
        sum += pulseIn(FR_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;
    
    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - FR_OFF;
    
    if(ENABLE_LOG_USS)
    {   
        Serial.print("\nFront-Right Dist:\t");
        Serial.println(dist);
    }
    
    return dist;
}

 float distBL()
{ 
    float sum = 0;
    float avrg, dist;

    //Take measurement samples
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(BL_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(BL_TRIG, LOW);
        
        sum += pulseIn(BL_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;
    
    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - BL_OFF;

    if(ENABLE_LOG_USS)
    {
        Serial.print("\nBack-Left Dist:\t");
        Serial.println(dist);
    }
    
    return dist;
}

 float distBR()
{ 
    float sum = 0;
    float avrg, dist;

    //Take measurement samples
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(BR_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(BR_TRIG, LOW);
        
        sum += pulseIn(BR_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;

    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - BR_OFF;
    
    if(ENABLE_LOG_USS)
    {
	    Serial.print("\nBack-Right Dist:\t");
	    Serial.println(dist);
    }
    
    return dist;
}

 float distR()
{ 
    float sum = 0;
    float avrg, dist;

    //Take measurement samples
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(R_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(R_TRIG, LOW);
        
        sum += pulseIn(R_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;
    
    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - R_OFF;
    
    if(ENABLE_LOG_USS)
    {
        Serial.print("\nRight Dist:\t");
        Serial.println(dist);
    }
    
    return dist;
}

 float distL()
{ 
    float sum = 0;
    float avrg, dist;

    //Take measurement samples
    for(int i = 0; i < NUM_SAMP; i++)
    { 
        digitalWrite(L_TRIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(L_TRIG, LOW);
        
        sum += pulseIn(L_ECHO, HIGH);
        delay(10);
    }
    
    //Average Samples
    avrg = sum/NUM_SAMP;
    
    //Divide by two to get TOF of Pulse to Object
    avrg = avrg/2;
    
    //Convert TOF to inches from robot edge
    dist = float(avrg/29)*0.394 - L_OFF;

    if(ENABLE_LOG_USS)
    {
        Serial.print("\nLeft Dist:\t");
        Serial.println(dist);
    }
    
    return dist;
}

//Returns the difference between the distance measurements of the two front USS's in inches
float getFrontDiff()
{
    float d1 = distFL();
    delay(10);
    float d2 = distFR();
    delay(10);

    float diff = d1-d2;

    if(ENABLE_LOG_USS)
    {
        Serial.print("\nFront Distance Difference:\t");
        Serial.println(diff);
    }

    return diff;
}

//Returns the difference between the distance measurements of the two back USS's in inches
float getBackDiff()
{
    float d1 = distBL();
    delay(10);
    float d2 = distBR();
    delay(10);

    float diff = d1-d2;
    
    if(ENABLE_LOG_USS)
    {
        Serial.print("\nBack Distance Difference:\t");
        Serial.println(diff);
    }

    return diff;
}

//Calculates Robot orientation angle using front two USS's (positive angle -> clockwise)
float getFrontAngle()
{   
    //Get distance difference of front USS's
    float distDiff = getFrontDiff();

    //Calculate angle of orientation in radians
    float angleDiffRad = atan(distDiff/FRONT_GAP);

    //convert angle to degrees
    float angleDiffDeg = (angleDiffRad/2/Pi)*360;

    if(ENABLE_LOG_USS)
    {
      Serial.print("\nFront Angle:\t");
      Serial.println(angleDiffDeg);
      Serial.println();
    }
    
    return angleDiffDeg;
}

//Calculates Robot orientation angle using back two USS's (positive angle -> counter-clockwise)
 float getBackAngle()
{
    //Get distance difference of back USS's
    float distDiff = getBackDiff();

    //Calculate angle of orientation in radians
    float angleDiffRad = atan(distDiff/FRONT_GAP);

    //convert angle to degrees
    float angleDiffDeg = (angleDiffRad/2/Pi)*360;

    if(ENABLE_LOG_USS)
    {
      Serial.print("\nBack Angle:\t");
      Serial.println(angleDiffDeg);
      Serial.println();
    }

    return angleDiffDeg;
}

