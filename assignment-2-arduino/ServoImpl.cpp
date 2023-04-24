#include "ServoImpl.h"
#include "Arduino.h"

ServoImpl::ServoImpl(int pin) {
    this->pin = pin;
}

void ServoImpl::on() {
    motor.attach(this->pin);
}

void ServoImpl::setPosition(int angle) {
    float coeff = (2250.0-750) / 180;
    motor.write(750 + angle*coeff);
}

void ServoImpl::off() {
    motor.detach();
}
