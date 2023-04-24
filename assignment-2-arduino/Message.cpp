#include "Message.h"

    Message::Message(String content){
        this->content = content;
    }

    String Message::getContent() {
        return this->content;
    }
