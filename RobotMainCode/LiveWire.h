

#ifndef __LIVEWIRE_H__
#define __LIVEWIRE_H__

#define INDICATOR       13
#define LIVEWIRE        34

#define MIN_THRESH      20
#define MAX_THRESH      5000

#define TIMEOUT         10      //ms (maximum pulse width)

#define SAMP_COUNT      50
#define BLINK_COUNT     3

void liveWireInit();
void toggleIndicator();
bool isOT();

#endif
