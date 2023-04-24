#ifndef __ILLUMINATELEDTASK__
#define __ILLUMINATELEDTASK__

#include "Task.h"
#include "Led.h"

class IlluminateLedTask: public Task {

private:
    int pin;
    Light* led;

public:
    IlluminateLedTask(int pin);
    void init(int period);
    void tick();
    void setActive(bool active);
};

#endif
