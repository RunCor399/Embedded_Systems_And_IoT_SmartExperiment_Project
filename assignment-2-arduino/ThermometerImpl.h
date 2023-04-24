#ifndef __ThermometerImpl__
#define __ThermometerImpl__

#include "Thermometer.h"

class ThermometerImpl: public Thermometer {
public:
    ThermometerImpl(int pin);
    float computeTemperature();

private:
    int pin;
};

#endif