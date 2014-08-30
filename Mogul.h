#pragma once

#include "Driver.h"
#include "LineTracer.h"
#include "StepDetector.h"
#include "Stepper.h"

class Mogul{
private:
	Driver *driver;
	LineTracer *lineTracer;
	StepDetector *stepDetector;
	Stepper *stepper;
	int phase;
	int runtime;
	int hillnum;
	bool sflag;
public:
	Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *stepper);
	~Mogul();
	bool run();
};
