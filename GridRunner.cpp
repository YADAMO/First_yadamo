#include "GridRunner.h"

RunPattern runPatterns[] = {
	RunPattern(1,1,1),
	RunPattern()
};

GridRunner::GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis){
	lineTracer = lt;
	driver = dr;
	stepper = sp;
	colorDetector = cd;
	distance = dis;
	patIndex = 0;
	curPattern = runPatterns[0];
	detected = false;
	spFlag = true;
	runtime = 0;
}

GridRunner::~GridRunner(){

}

void GridRunner::changePattern(){
	patIndex++;
	curPattern = runPatterns[patIndex];
	distance->init(0, 0);
	runtime = 0;
}

void GridRunner::goStraight(){
	if(distance->getDistance(0,0) < curPattern.param){
		driver->straight(40);
	}else{
		changePattern();
	}
}

void GridRunner::turn(){
	if(runtime < 500){
		driver->drive(100, 0);
	}else{
		changePattern();
	}
	runtime += 4;
}

bool GridRunner::run(){
	bool st = false;
	if(!spFlag){
		if(stepper->run(RIGHTEDGE)){
			spFlag = true;
		}
	}else{
		switch(curPattern.pattern){
			case GOSTRAIGHT:
			goStraight();
			break;

			case TURN:
			turn();
			break;

			default:
			driver->straight(0);
			st = true;
			break;
		}
	}
	return st;
}
