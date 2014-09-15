#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"


class Jumper
{
public:
	Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper);
	~Jumper();
	bool run();
private:
	int runtime;
	int phase;
	Stepper *stepper;
	Driver *driver;
	LineTracer *lineTracer;
};
