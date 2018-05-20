#include "dmstepper.h"
#include "speedfunctions.h"

/**
* Constructor
*/
DMStepper::DMStepper(int dirPin, int stepPin)
  :DMStepper("Stepper", dirPin, stepPin) {

}

DMStepper::DMStepper(String name, int dirPin, int stepPin){
  this->name = name;
  this->_dirPin = dirPin;
  this->_stepPin = stepPin;
  pinMode(_dirPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  this->_timer = new DMTimer();
}

void DMStepper::run(signed char dir, unsigned long speed, unsigned long stepsToGo){
  if(isRunning())
    return;

  if(stepsToGo == 0)
  {
    _isRunning = false;
    return;
  }

  this->_maxSpeedForThisMove = speed;
  this->_stepsAchievedForThisMove = 0;
  this->_totalStepsForThisMove = stepsToGo;
  this->_direction = invertDirection ? -dir : dir;
  this->_isRunning = true;

  digitalWrite(_dirPin, this->_direction > 0 ? HIGH : LOW);
}

void DMStepper::runTo(signed long position, unsigned long speed){
  signed long offset = position - (signed long)this->currentPosition;
  run((offset < 0) ? -1 : 1, speed, abs(offset));
}

bool DMStepper::update(){

  if(!_isRunning)
    return false;

  //adjust the speed according to acceleration and current step position
  unsigned long speedHz = speedAtStep(_maxSpeedForThisMove, acceleration, _totalStepsForThisMove, _stepsAchievedForThisMove);

  if(speedHz > veryMaxSpeed)
    speedHz = veryMaxSpeed;

  unsigned long periodUs = 1000000 / speedHz;

  if(!_timer->isTimeReached(micros(), periodUs))
    return false;

  //send step!
  digitalWrite(_stepPin, HIGH);
  digitalWrite(_stepPin, LOW);

  _stepsAchievedForThisMove++;
  this->currentPosition+=this->_direction;

  //All steps done?
  if(_stepsAchievedForThisMove >= _totalStepsForThisMove)
    _isRunning = false;

  return true;
}
