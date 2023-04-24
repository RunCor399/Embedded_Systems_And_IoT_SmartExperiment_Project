
#ifndef __COMMSERVICE__
#define __COMMSERVICE__

#include "Arduino.h"
#include "Message.h"

class CommService {

public:
    Message* currentMessage;
    bool messageAvailable;

    void init();
    void updateCurrentMessage(String content);
    bool isMessageAvailable();
    Message* receiveMessage();
    void sendMessage(String content);
};

extern CommService commInterface;

#endif
