#include "BlinkTask.h"
#include "Arduino.h"

/* Task for control the blinking of a led */
BlinkTask::BlinkTask(int pin) {
    this->pin = pin;
}

void BlinkTask::init(int period) {
    Task::init(period);
    this->led = new Led(pin);
    this->blinkState = OFF;
}

void BlinkTask::setActive(bool active) {
    Task::setActive(active);
    if (!active) {
        led->switchOff();
    }
    this->blinkState = OFF;
}

void BlinkTask::tick() {
    switch (blinkState) {
        case OFF: {
            led->switchOn();
            blinkState = ON;
            break;
        }
    
        case ON: {
            this->led->switchOff();
            this->blinkState = OFF;
            break;
        }

        case STATIC_ON: {
            this->led->switchOn();
            break;
        }
    }
}

/* This method sets the blinking led to Static */
void BlinkTask::setStatic(bool staticMode) {
    if (staticMode) {
        this->blinkState = STATIC_ON;
    }
}
