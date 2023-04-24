#ifndef __SONARIMPL__
#define __SONARIMPL__

#include "Sonar.h"
#include "ThermometerImpl.h"

class SonarImpl : public Sonar {

public:
    SonarImpl(int echoPin, int triggerPin, float currentTemperature);
    float readDistance();
    void setCurrentTemperature(float currentTemperature);
    
private:
    float durationToDistance(float duration);

    int echoPin;
    int triggerPin;
    float currentTemperature;
};

#endif
