#include "ExperimentStateTask.h"
#include "Arduino.h"

/* Task that manages the entire experiment */
ExperimentStateTask::ExperimentStateTask(BlinkTask* blinkTask, IlluminateLedTask* illuminateTask, PhysicsComputation* phy, ButtonTask* buttonTask) {
    this->blinkTask = blinkTask;
    this->illuminateTask = illuminateTask;
    this->phy = phy;
    this->buttonTask = buttonTask;
}

void ExperimentStateTask::init(int period) {
    Task::init(period);
    this->currentPeriod = period;
    this->internalState = INIT_STATE;
    this->timer = 0;
}

void ExperimentStateTask::tick() {

    switch (internalState) {

        /* Sets up all the subtasks and the variable for the experiment */
        case INIT_STATE: {
            commInterface.sendMessage("setup");
            commInterface.sendMessage(String(this->currentPeriod));

            this->blinkTask->setActive(true);
            this->blinkTask->setStatic(true);
            this->buttonTask->setActive(true);
            this->illuminateTask->setActive(true);
            this->internalState = RUNNING_STATE;
            this->phy->setPeriod(this->currentPeriod);
            commInterface.sendMessage("EXPERIMENT_RUNNING");
            this->timer = millis();
            
            break;
        }

        /* Computes and sends the stats during the experiments */
        case RUNNING_STATE: {

            this->phy->compute();

            float instantVelocity = phy->getCurrentVelocity()*1000;
            float instantAcceleration = phy->getCurrentAcceleration()*1000000;
            float actualPosition = phy->getPositionInPair();

            commInterface.sendMessage(String(actualPosition));
            commInterface.sendMessage(String(instantVelocity));
            commInterface.sendMessage(String(instantAcceleration));
            
            long t1 = millis();
            if (t1 - this->timer >= 20000 || this->buttonTask->getStatus()) {
                this->internalState = FINISHED_STATE;
                this->blinkTask->setActive(false);
                this->illuminateTask->setActive(false);
                this->buttonTask->setActive(false);
                this->blinkTask->setActive(true);
                commInterface.sendMessage("EXPERIMENT_FINISHED");
                this->timer = millis();

            }

            break;
        }

        /* Waits the input from the user */
        case FINISHED_STATE: {
            if(commInterface.isMessageAvailable()){
              Message* message = commInterface.receiveMessage(); 
              
              if(message->getContent() == "reset"){
                    this->blinkTask->setActive(false);
                    Task::setDone();
                }
                delete message;
            }
            
           break;
          }  
        }
    }
