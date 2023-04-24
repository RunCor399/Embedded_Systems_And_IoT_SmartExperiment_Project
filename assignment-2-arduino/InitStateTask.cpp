#include "InitStateTask.h"
#include "Arduino.h"
#include "BlinkTask.h"
#include <avr/sleep.h>

/* Task that manages the initial part of the expermiment */
InitStateTask::InitStateTask(BlinkTask* blinkTask, IlluminateLedTask* illuminateTask, Button* bStart, PIR* pir, PhysicsComputation* phy) {
    this->blinkTask = blinkTask;
    this->illuminateTask = illuminateTask;
    this->bStart = bStart;
    this->pir = pir;
    this->phy = phy;
}

void InitStateTask::init(int period) {
    Task::init(period);
    this->internalState = INIT_STATE;
    this->timer = 0;
    this->objectDetected = false;
    this->countDetection = 0;
    this->pressed = false;
}

void InitStateTask::tick() {

    switch (internalState) {

        /* Sets up all the subtasks and the variable for the intial part of the experiment */
        case INIT_STATE: {
            commInterface.sendMessage("INITIALIZATION");

            this->pressed = false;
            this->objectDetected = false;
            this->countDetection = 0;
            illuminateTask->setActive(true);
            this->internalState = WAITING_STATE;
            this->timer = millis();
            break;
        }

        /* Waits for an user input */
        case WAITING_STATE: {
            long t1 = millis();
            if(!this->pressed){
              this->pressed = this->bStart->isPressed();        
            }
      
            if (this->pressed) {
                if (phy->getPosition() <= 1) {
                    this->objectDetected = true;
                }
                this->countDetection++;
            }

            if (this->countDetection >= 5) {
                if (!this->objectDetected) {
                    this->blinkTask->setActive(true);
                    this->internalState = ERROR_STATE;
                    commInterface.sendMessage("ERROR");
                    this->timer = millis();
                } else {
                    Task::setDone();
                    this->internalState = INIT_STATE;
                }
            } else if (t1 - this->timer >= 5000) {
                this->internalState = POWERSAVE_STATE;
                this->illuminateTask->setActive(false);
                commInterface.sendMessage("POWERSAVE");
                this->timer = millis();
            }
            break;
        } 

        /* Turns arduino into sleep mode */
        case POWERSAVE_STATE: {
            attachInterrupt(digitalPinToInterrupt(2), this->wakeUp, CHANGE);

            set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
            sleep_enable();
            sleep_mode();

            sleep_disable();
            detachInterrupt(digitalPinToInterrupt(2));
            this->internalState = INIT_STATE;
            break;
        }
        
        /* Error state */
        case ERROR_STATE: {
            long t2 = millis();
            if (t2 - this->timer >= 2000) {
                this->blinkTask->setActive(false);
                this->internalState = INIT_STATE;
            }
            break;
        } 
    }
}

static void InitStateTask::wakeUp() {
}

/* This method returns the period for initialize the experiment */
int InitStateTask::getPeriod() {
    return this->phy->getPeriod();
}
