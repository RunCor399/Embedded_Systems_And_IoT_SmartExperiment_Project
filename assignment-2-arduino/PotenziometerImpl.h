#ifndef __POTENZIOMETERIMPL__
#define __POTENZIOMETERIMPL__

#include "Potenziometer.h"

class PotenziometerImpl: public Potenziometer {

public:
    PotenziometerImpl(int pin);
    int getValue();

private:
    int pin;

};

#endif