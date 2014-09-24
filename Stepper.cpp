#include "Stepper.h"

#define INSPEED 15
#define STEPFORWARD 60
#define FSTEPTIME 300
#define SSTEPTIME 500
#define STOPTIME 1000

Stepper::Stepper(StepDetector *sd, LineTracer *lt, Driver *dr, Pid *pd, Distance *dis){
	stepDetector = sd;
	lineTracer = lt;
	driver = dr;
	pid = pd;
	distance = dis;
	phase = 0;
	runtime = 0;
	sflag = false;
	stepSpeed = 40;
}

Stepper::~Stepper(){

}

bool Stepper::run(int edge){
	switch(phase){
		case 0://低速でぶつける
			pid->changePid(0.15, 0.001, 0.02);
			lineTracer->lineTrace(INSPEED, edge);
			if(stepDetector->detect() && runtime > 500){
				phase++;
				runtime = 0;
				distance->init();
			}
			break;
		case 1://ちょっと下がる
			lineTracer->lineTrace(-20, edge);
			if(distance->getDistance() > 10){
				phase++;
			}
			break;
		case 2://のぼる
			lineTracer->lineTrace(stepSpeed, edge);
			if(distance->getDistance() < -25){
				phase = 10;
			}
			if(stepDetector->detect()){
				stepSpeed += 2;
			}
			break;
		case 3://低速でぶつける
			lineTracer->lineTrace(15, edge);
			if(stepDetector->detect() && runtime > 500){
				phase++;
				runtime = 0;
			}
			break;
		case 4://前輪をまっすぐにする
		if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(0);
			if(runtime > 800){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 5://後輪を乗せる
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(80);
			if(runtime > 380){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 6:
			driver->straight(0);
			return true;
			break;
		case 10:
			driver->straight(0);
			runtime = 0;
			phase = 0;
			stepSpeed = 40;
			return true;
			break;

	}
	runtime += 4;
	return false;
}
