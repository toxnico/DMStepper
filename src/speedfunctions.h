#ifndef SPEED_FUNCTIONS_H
#define SPEED_FUNCTIONS_H

//duration of the acceleration phase in ms
unsigned long accelerationDuration(unsigned long maxSpeed, unsigned long acceleration);

//number of steps for a whole acceleration phase
unsigned long accelerationStepCount(unsigned long maxSpeed, unsigned long acceleration);

//number of steps for a real acceleration phase, according to the total distance we want to go
unsigned long realAccelerationStepCount(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo);

//Tells if we can to a full acceleration to maxSpeed
bool canAccelerateCompletely(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo);

//returns the speed at a given step
unsigned long speedAtStep(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo, unsigned long currentStep);
#endif //SPEED_FUNCTIONS_H
