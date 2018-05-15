#include "steppergroup.h"

DMStepper* StepperGroup::get(String name){
  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    if ((*it)->name == name)
      return (*it);
  }
  return NULL;
}

//Update all the motors
bool StepperGroup::update(){
  bool updated = false;

  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    updated = updated || (*it)->update();
  }

  return updated;
}

//tells if at least one motor of the group is running
bool StepperGroup::isRunning(){
  bool isRunning = false;

  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    isRunning = isRunning || (*it)->isRunning();
  }

  return isRunning;
}
