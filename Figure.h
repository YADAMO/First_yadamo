#pragma once
#include "LineTracer.h"
#include "ColorDetector.h"
#include "Driver.h"

using namespace ecrobot;

class Figure{
private:
	LineTracer *lineTracer;
	ColorDetector *colorDetector;
	Driver *driver;
	int runtime;
	bool detected;
public:
	Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver);
	~Figure();
	bool run();
};
