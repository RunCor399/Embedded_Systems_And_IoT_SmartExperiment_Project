#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
    timerFlag = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  this->tasksNumber = 0;
}

bool Scheduler::addTask(Task* task){
  if (this->tasksNumber < MAX_TASKS-1){
    this->taskList[this->tasksNumber] = task;
    this->tasksNumber++;
    return true;
  } else {
    return false; 
  }
}

/* This methods schedule the Tasks if activated */ 
void Scheduler::schedule(){   
  while (!timerFlag){}
  timerFlag = false;
  
  for (int i = 0; i < this->tasksNumber; i++){
    if (this->taskList[i]->isActive() && this->taskList[i]->updateAndCheckTime(this->basePeriod)){
      this->taskList[i]->tick();
    }
  }
}
