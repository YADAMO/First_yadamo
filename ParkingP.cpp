#include "ParkingP.h"

ParkingP::ParkingP(LineTracer *argLineTracer, Driver *argDriver, ColorDetector *cd, Distance *dis){
	lineTracer = argLineTracer;
	driver = argDriver;
	colorDetector = cd;
	distance = dis;
	runtime = 0;
	phase = 0;
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
			if(colorDetector->blackLineDetect() && runtime > 2000){
				changePhase();
			}
			lineTracer->changePid(0.15, 0.001, 0.0137);
			lineTracer->lineTrace(30, RIGHTEDGE);	
			break;
		case 1:
			if(distance->getDistance() < -24){
				changePhase();
				driver->straight(0);
			}else{
				lineTracer->lineTrace(30, RIGHTEDGE);
			}
			break;
		case 2:
			if(distance->getDistance() < -18){
				changePhase();
				driver->straight(0);
			}else{
				driver->straight(20);
			}
			break;
		case 3:
			if(runtime > 1000){
				changePhase();
			}
			driver->turn(50);
			break;
		case 4:
			if(distance->getDiff() > 400){
				changePhase();
			}
			driver->backDrive(40, 40);
			break;
		case 5:
			if(distance->getDistance() > 7.5){
				changePhase();
			}
			driver->straight(-30);
			break;
		case 6:
			if(runtime > 1000){
				changePhase();
			}
			driver->turn(-60);
			break;
		case 7:
			if(distance->getDiff() > 350){
				changePhase();
			}else{
				driver->backDrive(-40, 40);
			}
			break;
		case 8:
			changePhase();
			break;
		case 9:
			st = true;
			break;
	}
	runtime += 3;

	return st;
}
