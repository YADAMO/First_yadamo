#pragma once
//read neccessary header file
//#include header file of PID class
#include "Driver.h"
#include "SectionController.h"
#include "Pid.h"
// const float TARGET = 700;
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
  void lineTrace(int speed);
  void setTarget(float tar);
};
