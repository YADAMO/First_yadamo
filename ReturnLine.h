#pragma once
#include "LightSensor.h"
#include "Driver.h"

namespace std {}
using namespace std;

class ReturnLine
{
public:
	ReturnLine(Driver *argDriver, LightSensor *argLightSensor);
	~ReturnLine();
	void returnLine();
private:
	int returnLine_time;
	Driver *driver;
  	LightSensor *lightSensor;
};
