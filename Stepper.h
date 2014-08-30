#pragma once

#include "StepDetector.h"
#include "LineTracer.h"
#include "Driver.h"

class Stepper{
private:
	StepDetector *stepDetector;
	LineTracer *lineTracer;
	Driver *driver;
	int phase;
	int runtime;
	bool sflag;
public:
	Stepper(StepDetector *sd, LineTracer *lt, Driver *dr);
	~Stepper();
	bool run(int edge);
};
