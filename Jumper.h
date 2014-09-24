#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"
#include "Distance.h"
#include "StepDetector.h"

class Jumper
{
public:
	Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper, Distance *argDistance, StepDetector *sd);
	~Jumper();
	bool run();
private:
	int runtime;
	int phase;
	Stepper *stepper;
	Driver *driver;
	LineTracer *lineTracer;
	Distance *distance;
	StepDetector *stepDetector;
};
