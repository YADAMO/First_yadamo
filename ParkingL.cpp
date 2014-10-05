#include "ParkingL.h"

ParkingL::ParkingL(LineTracer *argLineTracer, Driver *argDriver, StepDetector *sd, Distance *dis){
	lineTracer = argLineTracer;
	driver = argDriver;
	stepDetector = sd;
	distance = dis;
	runtime = 0;
	phase = 0;
}

ParkingL::~ParkingL(){
}

void ParkingL::changePhase(){
	phase++;
	driver->straightInit();
	distance->init();
	runtime = 0;
}

bool ParkingL::run(){
	bool st = false;

	switch(phase){
		case 0:
			if(stepDetector->detect() && runtime > 500){
				changePhase();
			}
			lineTracer->lineTrace(25, RIGHTEDGE);
			break;
		case 1:
			if(distance->getDistance() > 6){
				changePhase();
				driver->straight(0);
			}else{
				driver->straight(-30);
			}
			break;
		case 2:
			if(runtime > 1000){
				changePhase();
			}
			driver->turn(80);
			break;
		case 3:
			if(distance->getDiff() > 385){
				changePhase();
			}
			driver->backDrive(40, 40);
			break;
		case 4:
			if(distance->getDistance() > 30){
				changePhase();
			}
			driver->straight(-30);
			break;
		case 5:
			if(runtime > 4000){
				changePhase();
			}
			driver->straight(0);
			break;
		case 6:
			if(distance->getDistance() < -25){
				changePhase();
			}
			driver->straight(30);
			break;
		case 7:
			if(distance->getDiff() > 440){
				changePhase();
			}
			driver->drive(30, 30);
			break;
		case 8:
			if(stepDetector->detect()){
				changePhase();
			}
			lineTracer->lineTrace(20, RIGHTEDGE);
			break;
		case 9:
			if(runtime > 500){
				changePhase();
			}
			driver->straight(0);
			break;
		case 10:
			st = true;
			break;
	}
	runtime += 3;

	return st;
}
