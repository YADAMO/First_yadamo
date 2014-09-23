#include "Mogul.h"

Mogul::Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *sp, Distance *ds){
	driver = dr;
	lineTracer = lt;
	stepDetector = sd;
	stepper = sp;
	distance = ds;
	phase = 0;
	runtime = 0;
	hillnum = 0;
	sflag = false;
}

Mogul::~Mogul(){

}

bool Mogul::run(){
	runtime += 4;
	switch(phase){
		case 0://段差に上る
			if(stepper->run(-1)){
				phase++;
				distance->init();
			}
			break;
		case 1://
			lineTracer->lineTrace(40, LEFTEDGE);
			if(distance->getDistance() < -55){
				phase++;
				distance->init();
			}
			break;
		case 2:
			driver->drive(-40, 50);
			if(distance->getDistance() < -10){
				phase++;
			}
			break;
		case 3:
			
			return true;
			break;

	}
	return false;
}
