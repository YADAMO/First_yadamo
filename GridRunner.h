#pragma once

#include "LineTracer.h"
#include "Driver.h"
#include "Stepper.h"
#include "ColorDetector.h"
#include "Distance.h"
#include "StepDetector.h"
#include "RunPattern.h"

class GridRunner{
private:
	LineTracer *lineTracer;
	Driver *driver;
	Stepper *stepper;
	ColorDetector *colorDetector;
	Distance *distance;
	StepDetector *stepDetector;
	int runtime;
	RunPattern curPattern;
	int patIndex;
	bool detected;
	bool spFlag;
	F32 disOffset;
	void back();
	void changePattern();
	void goStraight();
	void turn();
public:
	GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis, StepDetector *sd);
	~GridRunner();
	static RunPattern runPatterns[];
	bool run();
};

//RunPattern(pattern, param: distance or direction, param2: speed or angle)
RunPattern GridRunner::runPatterns[] = {
	RunPattern(TURN, LEFTEDGE, 45),
	RunPattern(GOSTRAIGHT, -30, 40),
	RunPattern(TURN, RIGHTEDGE, 45),
	RunPattern(GOSTRAIGHT, -100, 40),
	RunPattern()
};
