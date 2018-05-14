#ifndef DMSTEPPER_H
#define DMSTEPPER_H

#include <dmoscillator.h>

class DMStepper {
private: //private members
  bool _isRunning = false;
  int _dirPin = 0;
  int _stepPin = 0;
  signed char _direction = 0;
  DMOscillator *_oscillator;

public: //public members

  DMStepper(int dirPin, int stepPin);

  unsigned long currentPosition = 0;
  char direction = 1;// 1 or -1
  unsigned long speed = 0; //steps/s
  unsigned long acceleration = 1; //steps/s^2

  bool isRunning() { return _isRunning; }

  void run(signed char dir, unsigned long stepsToGo);

  bool update();
};

#endif //DMSTEPPER_H
