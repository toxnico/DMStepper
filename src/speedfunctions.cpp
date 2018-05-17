#include "speedfunctions.h"
#include <math.h>
#include <stdio.h>

//duration of the acceleration phase in ms
unsigned long accelerationDuration(unsigned long maxSpeed, unsigned long acceleration){
  if(acceleration == 0)
    return 0;
  return (maxSpeed*1000) / acceleration;
}

//number of steps for a whole acceleration phase
unsigned long accelerationStepCount(unsigned long maxSpeed, unsigned long acceleration){

  if(acceleration == 0)
    return 0;
  return (accelerationDuration(maxSpeed, acceleration) * maxSpeed)/2000;
}

//number of steps for a real acceleration phase, according to the total distance we want to go
unsigned long realAccelerationStepCount(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo){
  //number of steps to achieve a complete acceleration phase
  unsigned long accelerationDistance = accelerationStepCount(maxSpeed, acceleration);

  //if the total distance to go is greater than acceleration steps + deceleration steps, it's ok.
  if(stepsToGo > accelerationDistance*2)
    return accelerationDistance;

  return stepsToGo / 2;
}

//Tells if we can to a full acceleration to maxSpeed
bool canAccelerateCompletely(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo){
  unsigned long accelerationDistance = accelerationStepCount(maxSpeed, acceleration);
  unsigned long realAccelerationDistance = realAccelerationStepCount(maxSpeed, acceleration, stepsToGo);

  return realAccelerationDistance == accelerationDistance;
}

//returns the speed at a given step
unsigned long speedAtStep(unsigned long maxSpeed, unsigned long acceleration, unsigned long stepsToGo, unsigned long currentStep){

  if(currentStep == 0 || currentStep == stepsToGo)
    return 1;

  //easiest situation: acceleration -> full speed -> deceleration
  if(canAccelerateCompletely(maxSpeed, acceleration, stepsToGo)){

    unsigned long left = accelerationStepCount(maxSpeed, acceleration);
    unsigned long right = stepsToGo - left;

    unsigned long speed = maxSpeed;

    //acceleration phase?
    if(currentStep < left){
      speed = sqrt(currentStep * 2 * acceleration);
    }

    //deceleration phase?
    if(currentStep > right)
      speed = sqrt((stepsToGo - currentStep) * 2 * acceleration);

    if(speed > maxSpeed)
      return maxSpeed;

    return speed;
  }
  else { //distance too short to reach max speed
    if(currentStep <= stepsToGo / 2) //acceleration
      return sqrt(currentStep * 2 * acceleration);
    else //deceleration
      return sqrt((stepsToGo - currentStep) * 2 * acceleration);
  }

  //should never get here
  return -1;
}



#ifdef CATCH_CONFIG_MAIN
  #include "catch/catch.hpp"
  TEST_CASE("Acceleration duration", "[acceleration]"){

    REQUIRE(accelerationDuration(6000, 1) == 6000000);
    REQUIRE(accelerationDuration(6000, 2) == 3000000);
    REQUIRE(accelerationDuration(6000, 1000) == 6000);
    REQUIRE(accelerationDuration(6000, 0) == 0);

  }

  TEST_CASE("Acceleration step count", "[acceleration]"){

    REQUIRE(accelerationStepCount(6000, 1000) == 18000);
    REQUIRE(accelerationStepCount(5000, 2000) == 6250);
    REQUIRE(accelerationStepCount(5000, 0) == 0);

    REQUIRE(realAccelerationStepCount(6000, 1000, 40000) == 18000);
    REQUIRE(realAccelerationStepCount(5000, 2000, 6000) == 3000);
    REQUIRE(realAccelerationStepCount(5000, 0, 6000) == 0);
    REQUIRE(realAccelerationStepCount(6000, 6000, 40000) == 3000);

  }

  TEST_CASE("Speed at step", "[acceleration]"){

    SECTION( "Constant speed phase" ) {
      REQUIRE(speedAtStep(6000, 6000 , 40000, 4000) == 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 3001) == 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 2500) != 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 36999) == 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 38000) != 6000);
    }

    SECTION( "Acceleration phase" ) {
      REQUIRE(canAccelerateCompletely(6000, 6000, 40000) == true);
      REQUIRE(accelerationStepCount(6000, 6000) == 3000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 3000) == 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 0) == 1);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 1500) == 4242);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 500) < 4242);
    }

    SECTION( "Deceleration phase" ) {
      REQUIRE(canAccelerateCompletely(6000, 6000, 40000) == true);
      REQUIRE(accelerationStepCount(6000, 6000) == 3000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 37000) == 6000);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 0) == 1);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 40000) == 1);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 38500) == 4242);
      REQUIRE(speedAtStep(6000, 6000 , 40000, 39000) < 4242);
    }

    SECTION("No full acceleration"){
      unsigned long maxSpeed = 6000;
      unsigned long acceleration = 1000;
      unsigned long stepsToGo = 10000;
      REQUIRE(canAccelerateCompletely(maxSpeed, acceleration,  stepsToGo) == false);
      REQUIRE(speedAtStep(maxSpeed, acceleration,  stepsToGo, 5000) == 3162);// (unsigned long)(sqrt(5000 * 2 * acceleration));

      INFO("Start == End");
      REQUIRE(speedAtStep(maxSpeed, acceleration,  stepsToGo, 2500) == speedAtStep(maxSpeed, acceleration,  stepsToGo, 7500));


    }

  }
#endif
