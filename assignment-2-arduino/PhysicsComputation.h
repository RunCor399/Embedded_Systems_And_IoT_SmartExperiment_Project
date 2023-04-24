#ifndef __PHYSICSCOMPUTATION__
#define __PHYSICSCOMPUTATION__

#define MIN_SPEED 0
#define MAX_SPEED 100
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define PRECISION_FACTOR 100000


#include "SonarImpl.h"
#include "ThermometerImpl.h"
#include "ServoImpl.h"
#include "PotenziometerImpl.h"
#include "Pair.h"
#include "Math.h"



class  PhysicsComputation {

public:
    virtual void compute() = 0;
    virtual void setPeriod(int period);
    virtual void computeVelocity() = 0;
    virtual void computeAcceleration() = 0;
    virtual float getCurrentVelocity() = 0;
    virtual float getCurrentAcceleration() = 0;
    virtual float getPosition() = 0;
    virtual float getPositionInPair() = 0;
    virtual int getPeriod() = 0;
    virtual void setupSonar() = 0;
    virtual void setServoPosition() = 0;
    virtual bool objectTooFar(float pos2) = 0;
    virtual bool reduceError(float pos1, float pos2) = 0;
};

#endif
