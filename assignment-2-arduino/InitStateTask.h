#ifndef __INITSTATETASK__
#define __INITSTATETASK__

#include <avr/sleep.h>
#include "Task.h"
#include "Button.h"
#include "PIR.h"
#include "Sonar.h"
#include "Potenziometer.h"
#include "PhysicsComputation.h"
#include "BlinkTask.h"
#include "IlluminateLedTask.h"
#include "CommService.h"

class InitStateTask: public Task {

private:
    BlinkTask* blinkTask;
    IlluminateLedTask* illuminateTask;
    Button* bStart;
    PIR* pir;
    PhysicsComputation* phy;

    enum {INIT_STATE, WAITING_STATE, POWERSAVE_STATE, ERROR_STATE} internalState;
    long timer;
    bool objectDetected;
    int countDetection;
    bool pressed;

    static void wakeUp();

public:
    InitStateTask(BlinkTask* blinkTask, IlluminateLedTask* illuminateTask, Button* bStart, PIR* pir, PhysicsComputation* phy);
    void init(int period);
    void tick();
    int getPeriod();
};

#endif
