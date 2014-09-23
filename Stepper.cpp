#include "Stepper.h"

#define INSPEED 20
#define STEPFORWARD 60
#define FSTEPTIME 300
#define SSTEPTIME 500
#define STOPTIME 1000

Stepper::Stepper(StepDetector *sd, LineTracer *lt, Driver *dr, Pid *pd){
	stepDetector = sd;
	lineTracer = lt;
	driver = dr;
	pid = pd;
	phase = 0;
	runtime = 0;
	sflag = false;
}

Stepper::~Stepper(){

}

bool Stepper::run(int edge){
	switch(phase){
		case 0://低速でぶつける
			pid->changePid(0.2, 0.001, 0.03);
			lineTracer->lineTrace(INSPEED, edge);
			if(stepDetector->detect() && runtime > 500){
				phase++;
				runtime = 0;
			}
			break;
		case 1://ちょっと下がる
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(-20);
			if(runtime > 1500){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 2://のぼる
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(50);
			if(runtime > 800){
				phase++;
				runtime = 0;
				sflag = false;
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


	}
	runtime += 4;
	return false;
}
