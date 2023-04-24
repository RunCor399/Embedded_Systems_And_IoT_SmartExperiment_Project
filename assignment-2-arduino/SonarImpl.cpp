#include "SonarImpl.h"
#include "Arduino.h"

SonarImpl::SonarImpl(int echoPin, int triggerPin, float currentTemperature){
    this->echoPin = echoPin;
    this->triggerPin = triggerPin;
    this->currentTemperature = currentTemperature;

    pinMode(echoPin, INPUT);
    pinMode(triggerPin, OUTPUT);
}

float SonarImpl::readDistance(){
    digitalWrite(this->triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, LOW);

    float duration = pulseIn(echoPin, HIGH);

    float distance = this->durationToDistance(duration);

    return distance;
}

/* This methods return the distance from the object in meter with 3 decimal digits */
float SonarImpl::durationToDistance(float duration){
   const float sound_velocity = (331.45 + 0.62 * this->currentTemperature);
   float timeElapsed = duration / 1000.0 / 1000.0 / 2;

   return ((int)(timeElapsed * sound_velocity*1000.0))/1000.0;
}

void SonarImpl::setCurrentTemperature(float currentTemperature) {
    this->currentTemperature = currentTemperature;
}
