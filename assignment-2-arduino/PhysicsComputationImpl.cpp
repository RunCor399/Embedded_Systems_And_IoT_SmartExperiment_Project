#include "config.h"
#include "PhysicsComputationImpl.h"
#include "Arduino.h"

/* Task that contains all sensors and compute stats from the sensor's input*/
PhysicsComputationImpl::PhysicsComputationImpl(int initPeriod){
    this->thermometer = new ThermometerImpl(TERM_PIN);
    this->sonar = new SonarImpl(SONAR_ECHO_PIN, SONAR_TRIG_PIN, this->thermometer->computeTemperature());
    
    this->servo = new ServoImpl(SERVO_PIN);
    this->pot = new PotenziometerImpl(POT_PIN);
    this->positionValues = new Pair();
    this->velocityValues = new Pair();
    this->currentVelocity = 0;
    this->currentAcceleration = 0;
    this->period = initPeriod;
    this->servo->on();
    
}

void PhysicsComputationImpl::setPeriod(int period) {
    this->period = period;
    this->currentVelocity = 0;
    this->currentAcceleration = 0;
    this->positionValues->resetPair();
}

/* This method computes all the stats necessary for the experiment */
void PhysicsComputationImpl::compute() {
    this->setupSonar();

    if (this->positionValues->getSize() == 0){
        this->positionValues->addValueFront(this->sonar->readDistance());
    }
    else {
        float positionA = this->sonar->readDistance();

        this->positionValues->addValueBack(positionA);
		    this->computeVelocity();
    }

    if (this->velocityValues->getSize() == 0) {
		this->velocityValues->addValueFront(this->currentVelocity);
	}
	else {
		this->velocityValues->addValueBack(this->currentVelocity);
		this->computeAcceleration();
	}
}

/* This method computes the velocity of the object */
void PhysicsComputationImpl::computeVelocity(){
    float pos1 = this->positionValues->getFirstValue();
    float pos2 = this->positionValues->getSecondValue();

    if (this->objectTooFar(pos2) || this->reduceError(pos1, pos2)){
        this->currentVelocity = 0;
    }
    else {
      this->currentVelocity = abs((pos2 - pos1) / (this->period));
    }

    this->setServoPosition();
	
    this->positionValues->addValueFront(this->positionValues->getSecondValue());
	this->positionValues->addValueBack(-1);
}

/* This method computes the acceleration of the object */
void PhysicsComputationImpl::computeAcceleration(){
    float vel1 = this->velocityValues->getFirstValue();
    float vel2 = this->velocityValues->getSecondValue();
    
    this->currentAcceleration = abs((vel2 - vel1) / (this->period));
    
	  this->velocityValues->addValueFront(this->velocityValues->getSecondValue());
	  this->velocityValues->addValueBack(-1);
} 

void PhysicsComputationImpl::setupSonar(){
    this->sonar->setCurrentTemperature(this->thermometer->computeTemperature());
}

float PhysicsComputationImpl::getPosition(){
    this->setupSonar();
    return this->sonar->readDistance();
}

float PhysicsComputationImpl::getCurrentVelocity(){
    return this->currentVelocity;
}

float PhysicsComputationImpl::getCurrentAcceleration(){
    return this->currentAcceleration;
}

/* This method computes the frequency and return the period for the experiment */
int PhysicsComputationImpl::getPeriod() {
    int value = this->pot->getValue();
    value = map(value, 0, 1023, 1, 50);

    int period = (1000 / value);
    int computed_period = (period - (period % 20));

    return computed_period;
}

float PhysicsComputationImpl::getPositionInPair() {
  return this->positionValues->getFirstValue();
}

/* This method sets the angle for the Servo */
void PhysicsComputationImpl::setServoPosition() {
    int angle; 

    if (this->currentVelocity*PRECISION_FACTOR > MAX_SPEED){
        angle = MAX_ANGLE;
    }
    else{
        angle = map(int(this->currentVelocity*PRECISION_FACTOR), MIN_SPEED, MAX_SPEED, MIN_ANGLE, MAX_ANGLE);
    }

    this->servo->setPosition(angle);
}

/* This method checks if the object is too far for be detected in the experiment */
bool PhysicsComputationImpl::objectTooFar(float pos2) {
    return (pos2 > 1);
}

/* This methods controls the error of the Sonar */
bool PhysicsComputationImpl::reduceError(float pos1, float pos2) {
    return (abs(pos2 - pos1) < SONAR_ERROR && abs(pos2 - pos1) > 0);
}
