#pragma once
//read neccessary header file
//#include header file of PID class
#include "Driver.h"
#include "Pid.h"
#include "OffsetHolder.h"

#define RIGHTEDGE 1
#define LEFTEDGE -1

class Driver;
class LineTracer {
private:
//not define on UML
  Driver *driver;
  Pid *pid;
  OffsetHolder *offsetHolder;
  float target;
public:
	LineTracer(Driver *argDriver, Pid *argPid, OffsetHolder *oh);
	~LineTracer();
	void lineTrace(int speed, int adge);
	void setTarget(float target);
	float getTarget();
	void changePid(float p, float i, float d);
	void calcAllTarget();
	float nearblack;
	float nearnearblack;
	float nearnearwhite;
	float nearwhite;
};
