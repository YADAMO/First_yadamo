#include "Figure.h"

Figure::Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver){
	lineTracer = argLineTracer;
	colorDetector = argColorDetector;
	driver = argDriver;
	runtime = 0;
	detected = false;
}

Figure::~Figure(){
}

bool Figure::run(){
	if(runtime < 1000){
		detected = false;
		colorDetector->blackLineDetect();
		lineTracer->lineTrace(40, LEFTADGE);
	}else if(!detected){
		if(colorDetector->blackLineDetect()){
			detected =  true;
		}
		lineTracer->lineTrace(20, LEFTADGE);
	}else{
		driver->drive(0, 0);
	}
	runtime += 4;
	return true;
}
