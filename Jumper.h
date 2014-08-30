#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"

namespace std {}
using namespace std;

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
