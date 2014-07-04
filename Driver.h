#pragma once
//read neccessary header file
#include "Motor.h"
#include "LineTracer.h"

#define MAX_STEERING_ANGLE  270

using namespace ecrobot;

class Driver {
private:
  Motor *motorL;
  Motor *motorR;
  Motor *motorS;
public:
  Driver(Motor *L, Motor *R, Motor *S);
  ~Driver();   
  void drive(int turn, int speed); 
  void turn(int angle);
  void driveStraight(int distance);
};
