#ifndef __SERVO__
#define __SERVO__

class Servo {
    
public:
    virtual void on() = 0;
    virtual void setPosition(int angle) = 0;
    virtual void off() = 0;
};


#endif