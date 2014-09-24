#include "Jumper.h"

Jumper::Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper, Distance *argDistance, StepDetector *sd)
{
	phase = 0;
	stepper = argStepper;
	lineTracer = argLineTracer;
	driver = argDriver;
	distance = argDistance;
	stepDetector = sd;
}

Jumper::~Jumper()
{
}

//左エッジで復帰したい場合
//これのtrueを確認したあとに左エッジの低速ライントレース
bool Jumper::run()
{
	switch(phase){
		case 0://段差に上る
			if(stepper->run(RIGHTEDGE)){
				phase++;
				driver->straightInit();
				distance->init();
			}
			break;
		case 1:
			driver->straight(80);
			if(distance->getDistance() < -38){
				phase++;
			}
			break;
		case 2:
			driver->straight(40);
			if(distance->getDistance() < -55){
				phase++;
			}
			break;

		case 3:
			lineTracer->changePid(0.15, 0.001, 0.055);
			lineTracer->lineTrace(25, RIGHTEDGE);
			if(distance->getDistance() < -80){
				phase++;
			}
			break;
		case 4:
			distance->init();
			return true;
			break;

	}
	return false;
}
