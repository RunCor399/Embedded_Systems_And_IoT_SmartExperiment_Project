#include "config.h"
#include "Scheduler.h"
#include "IlluminateLedTask.h"
#include "BlinkTask.h"
#include "StateManagerTask.h"
#include "InitStateTask.h"
#include "Task.h"
#include "ExperimentStateTask.h"
#include "ButtonImpl.h"
#include "PIRImpl.h"
#include "PhysicsComputationImpl.h"
#include "ButtonTask.h"
#include "CommService.h"

Scheduler scheduler;

void setup(){
  scheduler.init(20);
  
  commInterface.init();


  PhysicsComputation* phy = new PhysicsComputationImpl(100);
  Button* bStart = new ButtonImpl(B_START_PIN);
  Button* bStop = new ButtonImpl(B_STOP_PIN);
  PIR* pir = new PIRImpl(PIR_PIN);
 
  Task* buttonTask = new ButtonTask(bStop);
  buttonTask->init(60);
  buttonTask->setActive(false);

  Task* blinkTask = new BlinkTask(RED_LED_PIN);
  blinkTask->init(200);
  blinkTask->setActive(false);

  Task* illuminateTask = new IlluminateLedTask(GREEN_LED_PIN);
  illuminateTask->init(100);
  illuminateTask->setActive(false);

  Task* initStateTask = new InitStateTask(blinkTask, illuminateTask, bStart, pir, phy);
  initStateTask->init(100);
  initStateTask->setActive(false);
  
  Task* experimentStateTask = new ExperimentStateTask(blinkTask, illuminateTask, phy, buttonTask);
  experimentStateTask->setActive(false);

  Task* stateManagerTask = new StateManagerTask(initStateTask, experimentStateTask);
  stateManagerTask->init(100);
  stateManagerTask->setActive(true);
   

  scheduler.addTask(buttonTask);
  scheduler.addTask(initStateTask);
  scheduler.addTask(experimentStateTask);
  scheduler.addTask(illuminateTask);
  scheduler.addTask(blinkTask);
  scheduler.addTask(stateManagerTask);
}

void loop(){
  scheduler.schedule();
}
