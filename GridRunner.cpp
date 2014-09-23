#include "GridRunner.h"

GridRunner::GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis, StepDetector *sd){
	lineTracer = lt;
	driver = dr;
	stepper = sp;
	colorDetector = cd;
	distance = dis;
	stepDetector = sd;
	patIndex = 0;
	curPattern = runPatterns[0];
	detected = false;
	spFlag = true;
	runtime = 0;
	disOffset = 0;
}

GridRunner::~GridRunner(){

}

void GridRunner::changePattern(){
	patIndex++;
	curPattern = runPatterns[patIndex];
	distance->init();
	driver->straightInit();
	runtime = 0;
}

void GridRunner::back(){
	if(distance->getDistance() - disOffset < 18){
		driver->drive(10, -30);
	}else{
		driver->straightInit();
		detected = false;
		runtime = 0;
	}
}

void GridRunner::goStraight(){
	if(stepDetector->detect() && runtime > 1000){
		detected = true;
		disOffset = distance->getDistance();
	}

	if(detected){
		back();
	}else if(distance->getDistance() > curPattern.param){
		driver->straight(curPattern.param2);
	}else{
		changePattern();
	}
}

void GridRunner::turn(){
	if(distance->getDiff() < (int)(490.0 * ((float)curPattern.param2 / 90.0))){
		driver->drive(90 * -curPattern.param, 0);
	}else{
		changePattern();
	}
}

bool GridRunner::run(){
	bool st = false;
	if(!spFlag){
		if(stepper->run(RIGHTEDGE)){
			spFlag = true;
			distance->init();
		}
	}else{
		switch(curPattern.pattern){
			case GOSTRAIGHT:
				goStraight();
				break;
			case TURN:
				turn();
				break;
			case 0:
				driver->straight(0);
				st = true;
				break;
		}
	}
	runtime += 4;
	return st;
}
