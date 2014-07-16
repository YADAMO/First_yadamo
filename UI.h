#pragma once
#include "LightSensor.h"
#include "TouchJudgement.h"
#include "LineTracer.h"
#include "Clock.h"
#include "Speaker.h"

class UI{
public:
	UI(LightSensor *light, TouchJudgement *touchJ, LineTracer *lineT, Clock *clk, Speaker *spk);
	~UI();
	void calibration(void);
private:
	LightSensor *lightSensor;
	TouchJudgement *touchJudgement;
	LineTracer *lineTracer;
	Clock *clock;
	Speaker *speaker;
	int touchCount;
	bool judge;
	S16 white, black;
};
