#pragma once

#include "LineTracer.h"
#include "Driver.h"
#include "Stepper.h"
#include "ColorDetector.h"

#define GOSTRAIGHT 1
#define TURNLEFT 2
#define TURNRIGHT 3

class GridRunner{
private:
	LineTracer *lineTracer;
	Driver *driver;
	Stepper *stepper;
	ColorDetector *colorDetector;
	// int scenario[15];
	int runtime;
	int curScene;
	bool detected;
	bool spFlag;
	bool goStraight();
	bool turnRight();
	bool turnLeft();
public:
	GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd);
	~GridRunner();
	bool run();
};
