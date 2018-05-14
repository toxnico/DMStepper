#include <dmtimer.h>
#include <dmoscillator.h>
#include "dmstepper.h"

DMTimer *t = NULL;
DMStepper *motor = NULL;

int dirPin = 22;
int stepPin = 23;
int stepsTotal = 40000;
char direction = 1;

void setup(){
  delay(1000);
  Serial.begin(115200);
  //configure the timer to trigger every second
  t = new DMTimer(1*1000000);

  motor = new DMStepper(dirPin, stepPin);
  motor->acceleration = 6000;

  Serial.println("Go!");
}

void loop(){

  //every second...
  if(t->isTimeReached()){


    motor->run(direction, stepsTotal, 6000);

    direction *= -1;
  }

  //update the motor
  motor->update();

}
