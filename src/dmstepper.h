#ifndef DMSTEPPER_H
#define DMSTEPPER_H

#include <dmtimer.h>

class DMStepper {
private: //private members
  bool _isRunning = false;
  int _dirPin = 0;
  int _stepPin = 0;
  signed char _direction = 0;

  //step counter for the current move
  unsigned long _stepsAchievedForThisMove = 0;
  unsigned long _totalStepsForThisMove = 0;

  unsigned long _maxSpeedForThisMove = 0;

  DMTimer *_timer;

public: //public members

  DMStepper(int dirPin, int stepPin);
  DMStepper(String name, int dirPin, int stepPin);

  String name;
  //Current position in steps.
  signed long currentPosition = 0;

  char direction = 1;// 1 or -1

  bool invertDirection = false;

  unsigned long acceleration = 300; //steps/s^2

  //limit speed
  unsigned long veryMaxSpeed = 13000; //steps/s

  bool isRunning() { return _isRunning; }

  //run for a number of steps in one direction or another
  void run(signed char dir, unsigned long stepsToGo, unsigned long speed);
  //run to absolute position
  void runTo(signed long position, unsigned long speed);

  bool update();
};

#endif //DMSTEPPER_H
