#include "ParkingP.h"

ParkingP::ParkingP(LineTracer *argLineTracer, Driver *argDriver, ColorDetector *cd, Distance *dis){
	lineTracer = argLineTracer;
	driver = argDriver;
	colorDetector = cd;
	distance = dis;
	runtime = 0;
	phase = 2;
}

ParkingP::~ParkingP(){
}

void ParkingP::changePhase(){
	phase++;
	driver->straightInit();
	distance->init();
	runtime = 0;
}

bool ParkingP::run(){
	bool st = false;

	switch(phase){
		case 0:
			if(colorDetector->blackLineDetect() && runtime > 1500){
				changePhase();
			}
			lineTracer->lineTrace(30, RIGHTEDGE);
			break;
		case 1:
			if(distance->getDistance() > 10){
				changePhase();
				driver->straight(0);
			}else{
				lineTracer->lineTrace(30, RIGHTEDGE);
			}
			break;
		case 2:
			if(runtime > 1000){
				changePhase();
			}
			driver->turn(70);
			break;
		case 3:
			if(distance->getDiff() > 400){
				changePhase();
			}
			driver->backDrive(70, 20);
			break;
		case 4:
			if(distance->getDistance() > 15){
				changePhase();
			}
			driver->straight(-30);
			break;
		case 5:
			if(runtime > 1000){
				changePhase();
			}
			driver->turn(-70);
			break;
		case 6:
			if(distance->getDiff() > 430){
				changePhase();
			}else{
				driver->backDrive(-70, 20);
			}
			break;
		case 7:
			if(runtime > 4000){
				changePhase();
			}
			driver->turn(-80);
			break;
		case 8:
			st = true;
			break;
	}
	runtime += 4;

	return st;
}
