#pragma once
#include "LightSensor.h"
#include "Pid.h"
#include "Driver.h"

namespace std {}
using namespace std;

class ReturnLine
{
public:
	ReturnLine(Driver *argDriver, Pid *argPid);
	~ReturnLine();
	void returnLine();
private:
	int returnLine_time;
	Driver *driver;
  	Pid *pid;
};