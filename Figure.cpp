#include "Figure.h"

Figure::Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp, OffsetHolder *of){
	lineTracer = argLineTracer;
	colorDetector = argColorDetector;
	driver = argDriver;
	stepper = sp;
	offsetHolder = of;
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
			lineTracer->setTarget((tmptarget + offsetHolder->getBlack() * 3) / 4);
		}else{
			tmptarget = lineTracer->getTarget();
		}
		runtime = 0;
	}else if(runtime < 1000){
		driver->straight(0);
	}else if(runtime < 3000){
		lineTracer->lineTrace(20, RIGHTEDGE);
	}else if(runtime < 4000){
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
	}else if(runtime < 10500){
		driver->drive(100, 0);
	}else if(runtime < 17500){
		lineTracer->lineTrace(20, LEFTEDGE);
	}else{
		driver->straight(0);
	}
	runtime += 4;
	return false;
}
