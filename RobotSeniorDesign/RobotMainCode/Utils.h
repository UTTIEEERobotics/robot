

#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>
#include "GlobalDefines.h"
#include "Motors.h"
#include "Ultrasonic.h"
#include "Field.h"
#include "Mapping.h"
#include "LiveWire.h"
#include "PiComm.h"
#include "LEDMatrix.h"
#include "Grabber.h"
#include "CameraLed.h"

//Time delay between taking angle/distance difference measurements
#define SAMPLE_DELAY            75                     //ms

//Maximum angle of robot orientation allowed after movement
#define MAX_ANGLE               1                       //deg

//Maximum distance difference between front/back USS's allowed after movement
#define MAX_DIST_DIFF           0.2                     //in

#define MIN_DIST_DIFF_SIDE		0.4

#define MIN_DIST_DIFF           0.8                     //in

//Degree of rotation used for each adjustment in fixDistDiff*()
#define STEP_ANGLE              1                       //deg

//Degree of rotation used for each adjustment in fixDistDiff*()
#define STEP_DIST               0.3                     //in

//How far the robot needs to move to go to next cell (cells are a square foot)
#define CELL_DIST				12                      //in   

#define MAX_STEP_COUNT			4


void utilInit();
void fixDistLeft();
void fixDistLeftCol();
void fixDistRight();
void fixDistRightCol();
void fixDistDiffFront();
void fixDistDiffBack();
void adjustOrientation();
void adjustSidePosition();
void adjustFrontBackPosition();
void nextCell();
void checkForOT();
void moveToCache();
void moveToStart();


#endif
