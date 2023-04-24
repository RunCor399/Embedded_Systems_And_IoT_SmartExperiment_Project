#ifndef __SONAR__
#define __SONAR__

#include "ThermometerImpl.h"

class Sonar {

public:
    virtual float readDistance() = 0;
    virtual float durationToDistance(float duration) = 0;
    virtual void setCurrentTemperature(float currentTemperature) = 0;
};

#endif
