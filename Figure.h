#pragma once
#include "LineTracer.h"
#include "ColorDetector.h"
#include "Driver.h"
#include "Stepper.h"
#include "OffsetHolder.h"

using namespace ecrobot;

class Figure{
private:
	LineTracer *lineTracer;
	ColorDetector *colorDetector;
	Driver *driver;
	Stepper *stepper;
	OffsetHolder *offsetHolder;
	int runtime;
	bool spFlag;
	bool detected;
	float tmptarget;
public:
	Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp, OffsetHolder *of);
	~Figure();
	bool run();
};
