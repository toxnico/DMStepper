#include <dmtimer.h>
#include <dmoscillator.h>
#include "dmstepper.h"
#include "steppergroup.h"

//DMTimer *t = NULL;
//DMStepper *motor = NULL;

StepperGroup *group = new StepperGroup();

int dirPin = 22;
int stepPin = 23;
int stepsTotal = 16000;
char direction = 1;

void setup(){
  delay(1000);
  Serial.begin(115200);
  //configure the timer to trigger every second
  //t = new DMTimer(1*1000000);
  group->add(new DMStepper("left", 22, 23));

  //motor = new DMStepper(dirPin, stepPin);
  //motor->acceleration = 40000;

  Serial.println("Go!");

}

void loop(){

  //update the motor
  if(!group->isRunning()){
    direction *= -1;
    
    group->get("left")->run(direction, 6000, stepsTotal);
    Serial.println("Go again!");
  }
  group->update();

}
