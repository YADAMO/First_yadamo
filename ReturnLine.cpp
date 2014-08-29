#include "ReturnLine.h"

ReturnLine::ReturnLine(Driver *argDriver, LightSensor *argLightSensor)
{
	returnLine_time = 0;
	driver = argDriver;
  	lightSensor = argLightSensor;
}

ReturnLine::~ReturnLine()
{
}

void ReturnLine::returnLine()
{
	if(returnLine_time < 3000){
		driver->drive(-40, 40);
	}else if(returnLine_time < 5000){
		driver->drive(-40, 0);
	}else if(returnLine_time < 8000){
		driver->drive(-40, -40);
	}else if(returnLine_time < 11000){
		driver->drive(0, 0);
	}else if(returnLine_time < 13000){
		driver->drive(40, 0);
	}else if(returnLine_time < 16000){
		driver->drive(0, 0);	
	}
	returnLine_time += 4;
}