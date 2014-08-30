#include "Jumper.h"

ReturnLine::ReturnLine(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper)
{
	jumper_time = 0;
	stepper = argStepper;
	lineTracer = argLineTracer;
	driver = argDriver;
}

ReturnLine::~ReturnLine()
{
}

//左エッジで復帰したい場合
//これのtrueを確認したあとに左エッジの低速ライントレース
bool ReturnLine::returnLineLeft()
{
	returnLine_time += 4;
	if(!black_isleft){
		if(returnLine_time < 3000){
			driver->drive(-40, 20);
			if(colorDetector->blackLineDetect()){
				black_isleft = true;
				returnLine_time = 0;
			}
			return false;
		}else if(returnLine_time < 5000){
			driver->drive(-40, 0);
			return false;
		}else if(returnLine_time < 8000){
			driver->drive(-40, -20);
			return false;
		}else if(returnLine_time < 11000){
			driver->drive(0, 0);
			return true;
		}
	}else{
		if(returnLine_time < 500){
			driver->drive(40, 20);
			return false;
		}else{
			driver->drive(0, 0);
			return true;
		}
	}
	return false;
}
