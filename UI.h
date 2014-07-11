#pragma once
#include "LightSensor.h"
#include "TouchJudgement.h"
#include "LineTracer.h"
#include "Clock.h"

class UI{
public:
	UI(LightSensor *light, TouchJudgement *touchJ, LineTracer *lineT, Clock *clk);
	~UI();
	void calibration(void);
private:
	LightSensor *lightSensor;
	TouchJudgement *touchJudgement;
	LineTracer *lineTracer;
	Clock *clock;
	int touchCount;
	bool judge;
	S16 white, black;
};
