#include "Jumper.h"

Jumper::Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper)
{
	runtime = 0;
	phase = 0;
	stepper = argStepper;
	lineTracer = argLineTracer;
	driver = argDriver;
}

Jumper::~Jumper()
{
}

//左エッジで復帰したい場合
//これのtrueを確認したあとに左エッジの低速ライントレース
bool Jumper::run()
{
	runtime += 4;
	switch(phase){
		case 0://段差に上る
			if(stepper->run(-1)){
				phase++;
				runtime = 0;
			}
			break;
		case 1://１秒止まる
			driver->straight(0);
			if(runtime > 1000){
				phase++;
				runtime = 0;
			}
			break;
		case 2://
			lineTracer->lineTrace(40, -1);
			if(runtime > 4000){
				phase++;
				runtime = 0;
			}
			break;
		case 3://
			driver->straight(-20);
			if(runtime > 1500){
				phase++;
				runtime = 0;
			}
			break;
		case 4:
			driver->straight(100);
			if(runtime > 1000){
				phase++;
				runtime = 0;
			}
			break;
		case 5:
			lineTracer->lineTrace(20, -1);
			return true;
			break;

	}
	return false;
}
