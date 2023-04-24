#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "Task.h"
#include "ButtonImpl.h"

class ButtonTask: public Task {

private:
    bool bPressed;
    int pin;
    Button* bStop;

public:
    ButtonTask(ButtonImpl* bStop);
    void init(int period);
    void setActive(bool newActive);
    void tick();
    bool getStatus();

};

#endif
