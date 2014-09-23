#include "Figure.h"

Figure::Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp){
	lineTracer = argLineTracer;
	colorDetector = argColorDetector;
	driver = argDriver;
	stepper = sp;
	runtime = 0;
	detected = false;
	spFlag = false;
	tmptarget = 0;
}

Figure::~Figure(){
}

bool Figure::run(){

	if(!spFlag){
		if(stepper->run(RIGHTEDGE)){
			spFlag = true;
			lineTracer->setTarget(tmptarget - 40);
		}else{
			tmptarget = lineTracer->getTarget();
		}
		runtime = 0;
	}else if(runtime < 1000){
		driver->straight(0);
	}else if(runtime < 3000){
		lineTracer->lineTrace(20, RIGHTEDGE);
	}else if(runtime < 4000){
		driver->straight(0);
	}else if(runtime < 5000){
		lineTracer->setTarget(tmptarget);
		detected = false;
		colorDetector->blackLineDetect();
		lineTracer->lineTrace(30, LEFTEDGE);
	}else if(!detected){
		if(colorDetector->blackLineDetect()){
			detected =  true;
			runtime = 10000;
		}
		lineTracer->lineTrace(20, LEFTEDGE);
	}else if(runtime < 11000){
		driver->straight(0);
	}else if(runtime < 11300){
		driver->straight(0);
	}else if(runtime < 12000){
		driver->straight(0);
	}else if(runtime < 12500){
		driver->drive(100, 0);
	}else{
		lineTracer->lineTrace(20, LEFTEDGE);
	}
	runtime += 4;
	return true;
}
