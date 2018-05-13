#include <dmtimer.h>
#include <dmoscillator.h>
#include "dmstepper.h"

DMTimer *t = NULL;
DMStepper *motor = NULL;

int dirPin = 22;
int stepPin = 23;
int stepsTotal = 1600;
char direction = 1;

void setup(){
  delay(1000);
  Serial.begin(115200);
  //configure the timer to trigger every second
  t = new DMTimer(1*1000000);

  motor = new DMStepper(dirPin, stepPin);

  Serial.println("Go!");
}

void loop(){

  //every second...
  if(t->isTimeReached()){

    motor->speed = 6000;
    motor->run(direction, stepsTotal);

    direction *= -1;
  }

  //update the motor
  motor->update();
  
}
