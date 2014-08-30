#include "Stepper.h"

#define INSPEED 20
#define STEPFORWARD 60
#define FSTEPTIME 300
#define SSTEPTIME 500
#define STOPTIME 1000

Stepper::Stepper(StepDetector *sd, LineTracer *lt, Driver *dr){
	stepDetector = sd;
	lineTracer = lt;
	driver = dr;
	phase = 0;
	runtime = 0;
	sflag = false;
}

Stepper::~Stepper(){

}

bool Stepper::run(int edge){
	switch(phase){
		case 0:
			lineTracer->lineTrace(INSPEED, edge);
			if(stepDetector->detect() && runtime > 500){
				phase++;
				runtime = 0;
			}
			break;
		case 1:
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
		case 2:
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
		case 3:
			lineTracer->lineTrace(15, edge);
			if(stepDetector->detect() && runtime > 500){
				phase++;
				runtime = 0;
			}
			break;

		case 4:
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(0);
			if(runtime > 5000){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 5:
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(-15);
			if(runtime > 1500){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 6:
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
		case 7:
			driver->straight(0);
			return true;
			break;


	}
	runtime += 4;
	return false;
}
