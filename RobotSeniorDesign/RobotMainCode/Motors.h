

#ifndef __MOTORS_H__
#define __MOTORS_H__

#define stepPin			2

#define FL_dir  8
#define FR_dir  9
#define BL_dir  10
#define BR_dir  11

#define step_delay 115 //us

#define in_sp_vert 864.8649 //sp per inch
#define in_sp_lat 1032.7
#define deg_sp 105

#define in_pix  (0.00245 * 0.75)

void motorInit();
void forward(float in);
void backward(float in);
void left(float in);
void right(float in);
void onlyLeft(float in);
void onlyRight(float in);
void cw(float deg);
void ccw(float deg);

#endif
