#pragma once
#include "LightSensor.h"

class Pid{
private:
    float delta;
    float kp;
    float ki;
    float kd;
    float diff[2];
    float integral;
    ecrobot::LightSensor lightSensor;
public:
	Pid();
  int calcTurn(float target);
};
