#include "ButtonTask.h"

/* Task for control a Button */
ButtonTask::ButtonTask(ButtonImpl* bStop) {
    this->pin = pin;
    this->bStop = bStop;
}

void ButtonTask::init(int period) {
    Task::init(period);
    this->bPressed = false;
}

void ButtonTask::setActive(bool newActive) {
    Task::setActive(newActive);
    if (newActive) {
        this->bPressed = false;
    }
}

void ButtonTask::tick() {
    if (this->bStop->isPressed()) {
        this->bPressed = true;
    }
}

/* This method returns the status of the Button */
bool ButtonTask::getStatus() {
    return this->bPressed;
}
