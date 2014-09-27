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
	bool turnflag;
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
//マス移動の距離 -20
//斜め移動の距離 -35
//90度旋回 382
//45度旋回 175
RunPattern GridRunner::runPatterns[] = {
	RunPattern(TURN, LEFTEDGE, 360),
	RunPattern(GOSTRAIGHT, -15, 40),
	RunPattern(TURN, RIGHTEDGE, 190),
	RunPattern(GOSTRAIGHT, -60, 40),
	RunPattern(TURN, RIGHTEDGE, 190),
	RunPattern(GOSTRAIGHT, -60, 40),
	RunPattern(0, 0, 0)
};
