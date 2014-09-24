#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"
#include "Distance.h"

class Jumper
{
public:
	Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper, Distance *argDistance);
	~Jumper();
	bool run();
private:
	int runtime;
	int phase;
	Stepper *stepper;
	Driver *driver;
	LineTracer *lineTracer;
	Distance *distance;
};
