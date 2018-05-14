#include "dmstepper.h"

/**
* Constructor
*/
DMStepper::DMStepper(int dirPin, int stepPin){
  _dirPin = dirPin;
  _stepPin = stepPin;
  pinMode(_dirPin, OUTPUT);
  _oscillator = new DMOscillator(stepPin, OscillationMode::count);
}

void DMStepper::run(signed char dir, unsigned long stepsToGo){
  if(isRunning())
    return;

  _direction = dir;
  digitalWrite(_dirPin, dir > 0 ? HIGH : LOW);
  _oscillator->oscillateHz(speed, stepsToGo);
}

bool DMStepper::update(){
  bool updated = _oscillator->update();

  if(updated)
    currentPosition += _direction;

  return updated;
}

//duration of the acceleration phase in ms
unsigned long DMStepper::accelerationDuration(maxSpeed, acceleration){
   return (maxSpeed*1000) / acceleration;
}

//number of steps during the acceleration phase
unsigned long stepCountDuringAcceleration(maxSpeed, acceleration){
  return (accelerationDuration(maxSpeed, acceleration) * maxSpeed)/2
}
