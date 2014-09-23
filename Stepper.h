#pragma once

#include "StepDetector.h"
#include "LineTracer.h"
#include "Driver.h"

class Stepper{
private:
	StepDetector *stepDetector;
	LineTracer *lineTracer;
	Driver *driver;
	Pid *pid;
	int phase;
	int runtime;
	bool sflag;
public:
	Stepper(StepDetector *sd, LineTracer *lt, Driver *dr,Pid *pd);
	~Stepper();
	bool run(int edge);
};
