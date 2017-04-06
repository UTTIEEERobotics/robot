/*
 * Prototypes and definitions for Ultrasonic Sensor Measurments
 */

#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#define FL_ECHO         26      //Front-Left Ultrasonic Sensor Echo Pin
#define FR_ECHO         28      //Front-Right Ultrasonic Sensor Echo Pin
#define BR_ECHO         45      //Back-Right Ultrasonic Sensor Echo Pin
#define BL_ECHO         47      //Back-Left Ultrasonic Sensor Echo Pin
#define R_ECHO          38      //Right Ultrasonic Sensor Echo Pin
#define L_ECHO          24      //Left Ultrasonic Sensor Echo Pin

#define FL_TRIG         31      //Front-Left Ultrasonic Sensor Trig Pin
#define FR_TRIG         32      //Front-Right Ultrasonic Sensor Trig Pin
#define BR_TRIG         48      //Back-Right Ultrasonic Sensor Trig Pin
#define BL_TRIG         22      //Back-Left Ultrasonic Sensor Trig Pin
#define R_TRIG          40      //Right Ultrasonic Sensor Trig Pin
#define L_TRIG          46      //Left Ultrasonic Sensor Trig Pin

#define OFF_DIST        12      //Known distance of detected object for offset calibration

#define FL_OFF          1.59       //Front-Left Offset from front edge of robot
//#define FL_OFF          0      
#define FR_OFF          1.51       //Front-Right Offset from front edge of robot
//#define FR_OFF          0       
#define R_OFF           3.80       //Right Offset from right edge of robot
//#define R_OFF           0       
#define BR_OFF          2.00       //Back-Right Offset from back edge of robot
//#define BR_OFF          0       
#define BL_OFF          1.50       //Back-Left Offset from beck edge of robot
//#define BL_OFF          0       
#define L_OFF           4.49       //Left Offset from left edge of robot  
//#define L_OFF           0       

#define FRONT_GAP       3.4375    //Distance between front two USS's (used for angle calc)
#define BACK_GAP        3.4375    //Distance between back two USS's (used for angle calc)

#define NUM_SAMP        10      //Number of samples per measurement  

const float Pi = 3.14159; 


void ussInit();
void getOffsets();
float getFrontDiff();
float getBackDiff();
float getFrontAngle();
float getBackAngle();
float distR();
float distL();
float distBR();
float distBL();
float distFL();
float distFR();


#endif
