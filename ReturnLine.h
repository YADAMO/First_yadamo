#pragma once
#include "LightSensor.h"
#include "ColorDetector.h"
#include "Driver.h"

namespace std {}
using namespace std;

class ReturnLine
{
public:
	ReturnLine(Driver *argDriver, LightSensor *argLightSensor, ColorDetector *argColorDetector);
	~ReturnLine();
	void returnLineLeft();
	void returnLineRight();
private:
	int returnLine_time;
	Driver *driver;
  	LightSensor *lightSensor;
  	ColorDetector *colorDetector;
};
