#ifndef __THERMOMETER__
#define __THERMOMETER__
#define VCC ((float)5)

class Thermometer {

public:
    virtual float computeTemperature() = 0;
};

#endif