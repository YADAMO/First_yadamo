#include "ReturnLine.h"

ReturnLine::ReturnLine(Driver *argDriver, LightSensor *argLightSensor, ColorDetector *argColorDetector)
{
	returnLine_time = 0;
	driver = argDriver;
  	lightSensor = argLightSensor;
  	ColorDetector = argColorDetector;
}

ReturnLine::~ReturnLine()
{
}

void ReturnLine::returnLineLeft()
{
	if(returnLine_time < 3000){
		driver->drive(-40, 20);
	}else if(returnLine_time < 5000){
		driver->drive(-40, 0);
	}else if(returnLine_time < 8000){
		driver->drive(-40, -20);
	}else if(returnLine_time < 11000){
		driver->drive(0, 0);
	}else if(returnLine_time < 13000){
		driver->drive(40, 20);
	}else if(returnLine_time < 16000){
		driver->drive(40, 0);
	}else if(returnLine_time < 18000){
		driver->drive(40, -20);
	}else{
		driver->drive(0, 0);
	}
	returnLine_time += 4;
}

void ReturnLine::returnLineRight()
{
	if(returnLine_time < 3000){
		driver->drive(-40, 20);
	}else if(returnLine_time < 5000){
		driver->drive(-40, 0);
	}else if(returnLine_time < 8000){
		driver->drive(-40, -20);
	}else if(returnLine_time < 11000){
		driver->drive(0, 0);
	}else if(returnLine_time < 13000){
		driver->drive(40, 20);
	}else if(returnLine_time < 16000){
		driver->drive(40, 0);
	}else if(returnLine_time < 18000){
		driver->drive(40, -20);
	}else{
		driver->drive(0, 0);
	}
	returnLine_time += 4;
}