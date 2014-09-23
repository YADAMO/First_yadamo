#pragma once

#include "Driver.h"
#include "LineTracer.h"
#include "StepDetector.h"
#include "Stepper.h"
#include "Distance.h"
#include "Motor.h"

class Mogul{
private:
	Driver *driver;
	LineTracer *lineTracer;
	StepDetector *stepDetector;
	Stepper *stepper;
	Distance *distance;
	Motor *rightMotor;
	Motor *leftMotor;
	int phase;
	int runtime;
	int hillnum;
	bool sflag;
public:
	Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *stepper, Distance *ds, Motor *rm, Motor *lm);
	~Mogul();
	bool run();
};
