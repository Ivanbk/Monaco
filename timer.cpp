#include "timer.h"

hw_timer_t* my_timer = nullptr;
bool timer_fired = false;

void IRAM_ATTR onTimer(){
    timer_fired = true;
}

void setupTimer(int frequency){
    my_timer = timerBegin(1, 800, true);
    timerAttachInterrupt(my_timer, &onTimer, true);
    timerAlarmWrite(my_timer, frequency, true);
    timerAlarmEnable(my_timer);
}

