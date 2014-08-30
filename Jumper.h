#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"

namespace std {}
using namespace std;

class ReturnLine
{
public:
	ReturnLine(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper);
	~ReturnLine();
	bool returnLineLeft();
	bool returnLineRight();
private:
	int jumper_time;
	Stepper *stepper;
	Driver *driver;
	LineTracer *argLineTracer;
};
