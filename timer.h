#ifndef Timer_H
#define Timer_H
#include <Arduino.h>

#define TIMER1_PERIOD 3000 //ms

extern hw_timer_t *my_timer;
extern bool timer_fired;

void IRAM_ATTR onTimer();

void setupTimer(int frequency);

#endif