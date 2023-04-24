#include "PIRImpl.h"
#include "Arduino.h"

PIRImpl::PIRImpl(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

int PIRImpl::detectPerson(){
    return digitalRead(this->pin);
}