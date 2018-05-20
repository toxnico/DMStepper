# DMStepper
Stepper motor driver for Arduino. It handles linear acceleration and deceleration.

To initiate a move on a motor, call its `run` method with the following parameters:
* direction : 1 or -1
* max speed in steps/s
* number of steps to go

Then in the `loop()` function, just call motor's `update()` method to actually move it.

If `update()` is called when the complete move is finished (or not initiated), it will do nothing. So update() can be called at any time.

```C++
//Create a motor, telling the direction and step pins
DMStepper motor(dirPin, stepPin);

motor.acceleration = 15000;

//Run the motor for 10000 steps, at a max speed of 3000 steps/s
motor.run(1, 3000, 10000);

//get or set the current position in steps
motor.currentPosition;

//Run the motor to the absolute position of 1640 steps, at 3000 steps/s max
motor.runTo(1640, 3000);


//And in the loop() function:
motor.update();

```
