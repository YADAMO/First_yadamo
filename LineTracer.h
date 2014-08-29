#pragma once
//read neccessary header file
//#include header file of PID class
#include "Driver.h"
#include "Pid.h"

#define LEFT -1
#define RIGHT 1

class Driver;
class LineTracer {
private:
//not define on UML
  Driver *driver;
  Pid *pid;
  float target;
public:
	LineTracer(Driver *argDriver, Pid *argPid);
	~LineTracer();
	void lineTrace(int speed, int adge);
	void setTarget(float target);
};
