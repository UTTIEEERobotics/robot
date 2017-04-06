

#ifndef __PICOMM_H__
#define __PICOMM_H__

#define PiStartPin    44

typedef enum {
  SLEEP,
  LID,
  DIE
}PiState_t;

void piCommInit();
void startPi();

#endif
