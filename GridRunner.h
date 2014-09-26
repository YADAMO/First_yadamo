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
	int phase;
	int closePhase;
	F32 disOffset;
	int exitline;
	void back();
	void changePattern();
	void changePhase();
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
	RunPattern(GOSTRAIGHT, -50, 40),
	RunPattern(TURN, RIGHTEDGE, 90),
	RunPattern(GOSTRAIGHT, -50, 40),
	RunPattern(TURN, LEFTEDGE, 45),
	RunPattern(GOSTRAIGHT, -40, 40),
	RunPattern(0, 0, 0)
};
