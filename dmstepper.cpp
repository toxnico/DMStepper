#include "dmstepper.h"
#include "speedfunctions.h"

/**
* Constructor
*/
DMStepper::DMStepper(int dirPin, int stepPin){
  _dirPin = dirPin;
  _stepPin = stepPin;
  pinMode(_dirPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  _timer = new DMTimer();
}

void DMStepper::run(signed char dir, unsigned long speed, unsigned long stepsToGo){
  if(isRunning())
    return;

  _maxSpeedForThisMove = speed;
  _stepsAchievedForThisMove = 0;
  _totalStepsForThisMove = stepsToGo;

  _direction = dir;
  digitalWrite(_dirPin, dir > 0 ? HIGH : LOW);

  _isRunning = true;
}

bool DMStepper::update(){

  if(!_isRunning)
    return false;

  //adjust the speed according to acceleration and current step position
  unsigned long speedHz = speedAtStep(_maxSpeedForThisMove, acceleration, _totalStepsForThisMove, _stepsAchievedForThisMove);
  //if(speedHz < veryMinSpeed)
  //  speedHz = veryMinSpeed;
  if(speedHz > veryMaxSpeed)
    speedHz = veryMaxSpeed;
  unsigned long periodUs = 1000000 / speedHz;

  if(!_timer->isTimeReached(micros(), periodUs))
    return false;

  //send step!
  digitalWrite(_stepPin, HIGH);
  digitalWrite(_stepPin, LOW);

  _stepsAchievedForThisMove++;
  //Serial.println(_stepsAchievedForThisMove, DEC);
  if(_stepsAchievedForThisMove >= _totalStepsForThisMove)
    _isRunning = false;

  return true;
}
