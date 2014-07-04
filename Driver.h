#pragma once
//read neccessary header file
#include "Motor.h"
#include "LineTracer.h"

#define MAX_STEERING_ANGLE  270

// using namespace ecrobot

class Driver {
private:
  ecrobot::Motor *motorL;
  ecrobot::Motor *motorR;
  ecrobot::Motor *motorS;
public:
  Driver(ecrobot::Motor *L, ecrobot::Motor *R, ecrobot::Motor *S);
  ~Driver();   
  void drive(int turn, int speed); 
  void turn(int angle);
  void driveStraight(int distance);
};
