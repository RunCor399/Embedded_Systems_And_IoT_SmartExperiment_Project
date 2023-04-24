#include "StateManagerTask.h"
#include "Arduino.h"

/* Task that manages all the other tasks, activating and deactivating them */
StateManagerTask::StateManagerTask(InitStateTask* initStateTask, ExperimentStateTask* experimentStateTask) {
    this->initStateTask = initStateTask;
    this->experimentStateTask = experimentStateTask;
}

void StateManagerTask::init(int period) {
    Task::init(period);
    this->externalState = INIT_STATE;
    this->freq = 0;
}

void StateManagerTask::tick() {
    switch (externalState) {

        /* Sets active the InitTask and wait until it's done for initialize the experiment with its period */
        case INIT_STATE: {
            if (!this->initStateTask->isActive()) {
                this->initStateTask->setActive(true);
            } else if (initStateTask->isDone()) {
                this->freq = this->initStateTask->getPeriod();
                this->experimentStateTask->init(this->freq);
                this->experimentStateTask->setActive(true);
                this->initStateTask->setActive(false);
                this->freq = 0;
                this->externalState = EXPERIMENT_STATE;
            }
            break;
        }

        /* Waits until the ExperimentTask is done for reinitialize the experiment */
        case EXPERIMENT_STATE: {
            if (this->experimentStateTask->isDone()) {
                this->experimentStateTask->setActive(false);
                this->externalState = INIT_STATE;   
            }
            break;
        }
    }
}
