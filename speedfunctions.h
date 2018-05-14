#ifndef SPEED_FUNCTIONS_H
#define SPEED_FUNCTIONS_H

//Returns the duration of acceleration phase in ms
unsigned long accelerationDuration(unsigned long maxSpeed, unsigned long acceleration);

//Number of steps during acceleration phase
unsigned long accelerationStepCount(unsigned long maxSpeed, unsigned long acceleration);

unsigned long realAccelerationStepCount(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo);

#endif //SPEED_FUNCTIONS_H
