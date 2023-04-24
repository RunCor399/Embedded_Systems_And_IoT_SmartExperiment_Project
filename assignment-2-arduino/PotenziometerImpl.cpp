#include "PotenziometerImpl.h"
#include "Arduino.h"

PotenziometerImpl::PotenziometerImpl(int pin){
    this->pin = pin;    
}

int PotenziometerImpl::getValue(){
    int value = analogRead(this->pin);
    return value;
}
