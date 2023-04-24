#ifndef __STATEMANAGERTASK__
#define __STATEMANAGERTASK__

#include "Task.h"
#include "ExperimentStateTask.h"
#include "InitStateTask.h"

class StateManagerTask: public Task {

private:
    InitStateTask* initStateTask;
    ExperimentStateTask* experimentStateTask;
    int freq;
    enum {INIT_STATE, EXPERIMENT_STATE} externalState;

public:
    StateManagerTask(InitStateTask* initStateTask, ExperimentStateTask* experimentStateTask);
    void init(int period);
    void tick();
};

#endif
