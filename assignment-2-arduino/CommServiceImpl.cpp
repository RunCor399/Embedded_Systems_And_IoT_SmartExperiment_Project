#include "Arduino.h"
#include "CommService.h"

String content;
CommService commInterface;


/* Class for sends and recives message by Serial */
void CommService::init(){
    Serial.begin(115200);
    this->currentMessage = NULL;
    this->messageAvailable = false;
}

Message* CommService::receiveMessage(){
    if (this->messageAvailable) {
        Message* message = this->currentMessage;
        this->messageAvailable = false;
        this->currentMessage = NULL;
        content = "";

        return message;
    }
    else {
      return NULL;
    }
}

void CommService::sendMessage(String content) {
    Serial.println(content);
}

void CommService::updateCurrentMessage(String content) {
    this->currentMessage = new Message(content);
}

void serialEvent() {
    while (Serial.available()) {
        char ch = (char) Serial.read();
        if (ch == '\n'){
            commInterface.updateCurrentMessage(content);
            commInterface.messageAvailable = true;
        }  
     else {
        content += ch;      
    } 
   }
}

bool CommService::isMessageAvailable() {
    return this->messageAvailable;
}
