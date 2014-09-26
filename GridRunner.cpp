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
	closePhase = 0;
	phase = 0;
	runtime = 0;
	disOffset = 0;
	direction = 0;
	exitline = 3;
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

void GridRunner::changePhase(){
	phase++;
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
	if(runtime > 1000){
		driver->turn(60 * -curPattern.param);
	}else if(distance->getDiff() < (int)(360.0 * ((float)curPattern.param2 / 90.0))){
		driver->drive(60 * -curPattern.param, 0);
	}else{
		changePattern();
	}
}

bool GridRunner::run(){
	bool st = false;
	switch(phase){
		case 0:
		if(stepper->run(RIGHTEDGE)){
			changePhase();
		}
		break;

		case 1:
		switch(curPattern.pattern){
			case GOSTRAIGHT:
				goStraight();
				break;
			case TURN:
				turn();
				break;
			case 0:
				driver->straight(0);
				changePhase();
				break;
		}
		break;

		case 2:
		switch(closePhase){
			case 0:
				if(exitline > 3){
					closePhase = 4;
				}else{
					closePhase = 1;
				}
				break;
			case 1:
				if(runtime < 1000){
					driver->turn(-60);
				}else if(distance->getDiff() < 360.0){
					driver->drive(-60, 0);
				}else{
					closePhase = 3;
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 2:
				if(distance->getDistance() > -40 * (3 - exitline)){
					driver->straight(60);
				}else{
					closePhase = 3;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 3:
				if(colorDetector->blackLineDetect() && runtime > 500){
					closePhase = 4;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}else{
					driver->straight(40);
				}
				break;
			case 4:
				if(runtime < 1000){
					driver->turn(60);
				}else if(distance->getDiff() < 360){
					driver->drive(60, 0);
				}else{
					closePhase = 5;
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 5:
				lineTracer->changePid(0.15, 0.001, 0.055);
				lineTracer->lineTrace(25, RIGHTEDGE);
				if(distance->getDistance() < -80){
					closePhase = 6;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 6:
				changePhase();
				driver->straight(0);
				break;
		}
		break;

		case 3:
		st = true;
		driver->straight(0);
		break;
	}
	runtime += 4;
	return st;
}
