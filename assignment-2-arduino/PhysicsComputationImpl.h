#ifndef __PHYSICSCOMPUTATIONIMPL__
#define __PHYSICSCOMPUTATIONIMPL__

#include "PhysicsComputation.h"

class PhysicsComputationImpl : public PhysicsComputation {

public:
    PhysicsComputationImpl(int initPeriod);
    void compute();
    void setPeriod(int period);
    void computeVelocity();
    void computeAcceleration();
    float getCurrentVelocity();
    float getCurrentAcceleration();
    float getPosition();
    float getPositionInPair();
    int getPeriod();
    void setupSonar();
    void setServoPosition();
    bool objectTooFar(float pos2);
    bool reduceError(float pos1, float pos2);

private:
    Sonar* sonar;
    Thermometer* thermometer;
    Servo* servo;
    Potenziometer* pot;
    Pair* positionValues;
    Pair* velocityValues;
    int period;
    float currentVelocity;
    float currentAcceleration;
};

#endif
