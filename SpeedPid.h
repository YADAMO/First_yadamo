#pragma once
#include "SpeedMeter.h"

using namespace ecrobot;

class SpeedPid{
private:
    float delta;
    float kp;
    float ki;
    float kd;
    float diff[2];
    float integral;
	SpeedMeter *speedMeter;
public:
	SpeedPid(SpeedMeter *sm);
	void changePid(float p, float i, float d);
	int calcSpeed(float target);
};
