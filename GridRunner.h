#pragma once

#include "LineTracer.h"
#include "Driver.h"
#include "Stepper.h"
#include "ColorDetector.h"
#include "Distance.h"
#include "RunPattern.h"

class GridRunner{
private:
	LineTracer *lineTracer;
	Driver *driver;
	Stepper *stepper;
	ColorDetector *colorDetector;
	Distance *distance;
	int runtime;
	RunPattern curPattern;
	int patIndex;
	bool detected;
	bool spFlag;
	void goStraight();
	void turn();
	void changePattern();
public:
	GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis);
	~GridRunner();
	bool run();
};
