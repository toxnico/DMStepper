/*
This minimal sketch shows how to run a stepper motor.
The default acceleration is 300 steps/s².
On my driver, I used a microstepping of 1/8th step on a 200 steps/revolution motor, so values can seem high.

For every movement, call run() on the motor.
In the main loop, call update(), and that's it!

Nico
*/

#include "dmstepper.h"

DMStepper motor(22, 23);

void setup(){
  //Declare a motor on pins 22 (direction) and 23 (steps)

  //Acceleration of 35000 steps/s²
  motor.acceleration = 35000;

  //Initiate a movement of 16000 steps at a max speed of 12000 steps/s,
  //in direction 1 (direction can be inverted with motor->invertDirection = true)
  motor.run(1, 12000, 16000);

}

void loop(){

  //update motor position.
  //If the number of steps is reached, update() does nothing.
  motor.update();

  //if we want to restart the motor after, we can do this:
  // if(!motor.isRunning()){
  //   motor.run(1, 12000, 16000);
  // }

}
