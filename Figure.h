#pragma once
#include "LineTracer.h"
#include "ColorDetector.h"
#include "Driver.h"
#include "Stepper.h"

using namespace ecrobot;

class Figure{
private:
	LineTracer *lineTracer;
	ColorDetector *colorDetector;
	Driver *driver;
	Stepper *stepper;
	int runtime;
	bool spFlag;
	bool detected;
	float tmptarget;
public:
	Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp);
	~Figure();
	bool run();
};
