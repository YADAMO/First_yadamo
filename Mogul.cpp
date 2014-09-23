#include "Mogul.h"

Mogul::Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *sp, Distance *ds, Motor *rm, Motor *lm){
	driver = dr;
	lineTracer = lt;
	stepDetector = sd;
	stepper = sp;
	distance = ds;
	rightMotor = rm;
	leftMotor = lm;
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
				runtime = 0;
			}
			break;
		case 1://
			lineTracer->lineTrace(40, LEFTEDGE);
			if(runtime > 1000){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 2://
			if(!sflag){
				driver->straightInit();
				sflag = true;
			}
			driver->straight(40);
			if(runtime > 1200){
				phase++;
				runtime = 0;
				sflag = false;
			}
			break;
		case 4:
			lineTracer->lineTrace(20, -1);
			break;

	}
	return false;
}
