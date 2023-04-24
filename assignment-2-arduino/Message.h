#ifndef __MESSAGE__
#define __MESSAGE__

#include "Arduino.h"

class Message {

private:
    String content;

public:
    Message(String content);
    String getContent();
};

#endif