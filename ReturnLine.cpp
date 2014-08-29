#include "ReturnLine.h"

ReturnLine::ReturnLine(Driver *argDriver, Pid *argPid)
{
	returnLine_time = 0;
	driver = argDriver;
  	pid = argPid;
}

ReturnLine::~ReturnLine()
{
}

void ReturnLine::returnLine()
{
	if(returnLine_time < 4000){
		driver->drive(-60, 30);
	}else if(returnLine_time < 8000){
		driver->drive(-60, -30);
	}else if(returnLine_time < 12000){
		driver->drive(60, 30);
	}else{
		driver->drive(60, -30);	
	}
	returnLine_time += 4;
}