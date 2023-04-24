#ifndef __EXPERIMENTSTATETASK__
#define __EXPERIMENTSTATETASK__

#include "Task.h"
#include "PhysicsComputation.h"
#include "ButtonTask.h"
#include "BlinkTask.h"
#include "IlluminateLedTask.h"
#include "CommService.h"

class ExperimentStateTask: public Task {

private:
    BlinkTask* blinkTask;
    IlluminateLedTask* illuminateTask;
    PhysicsComputation* phy;
    ButtonTask* buttonTask;

    enum {INIT_STATE, RUNNING_STATE, FINISHED_STATE} internalState;
    long timer;
    int currentPeriod;

public:
    ExperimentStateTask(BlinkTask* blinkTask, IlluminateLedTask* illuminateTask, PhysicsComputation* phy, ButtonTask* buttonTask);
    void init(int period);
    void tick();
    
};

#endif
