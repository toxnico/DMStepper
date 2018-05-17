# DMStepper
Stepper motor driver for Arduino.

```C++
//Create a motor, telling the direction and step pins
DMStepper motor(dirPin, stepPin);


int direction = 1; //can be 1 or -1

//Run the motor for 10000 steps, at a max speed of 3000 steps/s
motor->run(direction, 3000, 10000);

//And in the loop() function:
motor->update();

```
