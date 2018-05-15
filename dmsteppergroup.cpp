#include "dmsteppergroup.h"

//Gets a motor by name
DMStepper* DMStepperGroup::get(String name){
  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    if ((*it)->name == name)
      return (*it);
  }
  return NULL;
}

//Update all the motors
bool DMStepperGroup::update(){
  bool updated = false;

  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    updated = updated || (*it)->update();
  }

  return updated;
}

//Tells if at least one motor of the group is running
bool DMStepperGroup::isRunning(){
  bool isRunning = false;

  for (std::vector<DMStepper*>::iterator it = _list.begin() ; it != _list.end(); ++it){
    isRunning = isRunning || (*it)->isRunning();
  }

  return isRunning;
}
