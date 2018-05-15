# DMStepper
Stepper motor driver for Arduino (currently in development, not packaged as library yet).

```C++
//Create a motor, telling the direction and step pins
DMStepper *motor = new DMStepper(dirPin, stepPin);


int direction = 1; //can be 1 or -1

//Run the motor for 10000 steps, at a speed of 3000 steps/s
motor->run(direction, 3000, 10000);

//And in the loop() function:
motor->update();


```
