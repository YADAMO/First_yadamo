#pragma once
#include "LightSensor.h"
#include "ColorDetector.h"
#include "Driver.h"

using namespace std;

class ReturnLine
{
public:
	ReturnLine(Driver *argDriver, LightSensor *argLightSensor, ColorDetector *argColorDetector);
	~ReturnLine();
	bool returnLineLeft();
	bool returnLineRight();
private:
	int returnLine_time;
	bool black_isleft;
	Driver *driver;
  	LightSensor *lightSensor;
  	ColorDetector *colorDetector;
};
