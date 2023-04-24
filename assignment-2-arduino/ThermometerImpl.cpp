#include "ThermometerImpl.h"
#include "Arduino.h"

ThermometerImpl::ThermometerImpl(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

float ThermometerImpl::computeTemperature(){
    int value = analogRead(this->pin);
    float valueInVolt = value*VCC/1023;  
    float valueInCelsius = valueInVolt/0.01;

    return valueInCelsius;
}