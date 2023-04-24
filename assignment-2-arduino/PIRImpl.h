#ifndef __PIRIIMPL__
#define __PIRIMPL__

#include "PIR.h"

class PIRImpl: public PIR {

public:
    PIRImpl(int pin);
    int detectPerson();

private:
    int pin;
};

#endif
