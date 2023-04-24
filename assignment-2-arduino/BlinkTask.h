#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {

private:
    int pin;
    Light* led;
    enum {ON, OFF, STATIC_ON} blinkState;

public:
    BlinkTask(int pin);
    void init(int period);
    void tick();
    void setActive(bool active);
    void setStatic(bool staticMode);
};

#endif
