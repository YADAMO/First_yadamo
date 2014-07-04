#pragma once
#include "LightSensor.h"

using namespace ecrobot;

class Pid{
private:
    float delta;
    float kp;
    float ki;
    float kd;
    float diff[2];
    float integral;
	LightSensor *lightSensor;
public:
	Pid(LightSensor *light);
	
  int calcTurn(float target);
};
