#include "IlluminateLedTask.h"
#include "Arduino.h"

/* Task that controls the illumination of a led */
IlluminateLedTask::IlluminateLedTask(int pin) {
    this->pin = pin;
}

void IlluminateLedTask::init(int period) {
    Task::init(period);
    led = new Led(pin);
}

void IlluminateLedTask::setActive(bool active) {
    Task::setActive(active);
    if (!active) {
        led->switchOff(); 
    }
}

void IlluminateLedTask::tick() {
    if (!led->isActive()) {
        led->switchOn();
    } 
}
