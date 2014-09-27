#include "GridRunner.h"

#define EXITLINE 2

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
	turnflag = false;
	runtime = 0;
	disOffset = 0;
}

GridRunner::~GridRunner(){

}

void GridRunner::changePhase(){
	phase++;
	distance->init();
	driver->straightInit();
	runtime = 0;
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
	if(stepDetector->detect() && runtime > 3000){
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
	if(distance->getDiff() < curPattern.param2 && !turnflag){
		if(runtime < 1000){
			driver->turn(60 * -curPattern.param);
		}else{
			driver->drive(60 * -curPattern.param, 0);
		}
	}else{
		if(turnflag){
			if(runtime < 1000){
				driver->turn(0);
			}else{
				changePattern();
				turnflag = false;
			}
		}else{
			turnflag = true;
			runtime = 0;
		}
	}
}

bool GridRunner::run(){
	bool st = false;
	switch(phase){
		case 0:
		if(stepper->gridStep(RIGHTEDGE)){
			changePhase();
		}
		break;

		// case 1:
		// if(distance->getDistance() > 5){
		// 	lineTracer->lineTrace(RIGHTEDGE, 15);
		// }else{
		// 	changePhase();
		// }
		// break;

		case 1:
		switch(curPattern.pattern){
			case GOSTRAIGHT:
				goStraight();
				break;
			case TURN:
				turn();
				break;
			default:
				driver->straight(0);
				changePhase();
				break;
		}
		break;

		case 2:
		switch(closePhase){
			case 0:
				if(EXITLINE > 3){
					closePhase = 4;
				}else{
					closePhase = 1;
				}
				break;
			case 1:
				if(distance->getDiff() < 340 && !turnflag){
					if(runtime < 1000){
						driver->turn(-60);
					}else{
						driver->drive(-60, 0);
					}
				}else{
					if(turnflag){
						if(runtime < 1000){
							driver->turn(0);
						}else{
							closePhase = 3;
							distance->init();
							driver->straightInit();
							runtime = 0;
							turnflag = false;
						}
					}else{
						turnflag = true;
						runtime = 0;
					}
				}
				break;
			case 3:
				if(colorDetector->blackLineDetect() && runtime > 10){
					closePhase = 4;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}else{
					driver->straight(40);
				}
				break;
			case 4:
				if(distance->getDistance() > -9){
					driver->straight(40);
				}else{
					closePhase = 5;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 5:
				if(runtime < 1000){
					driver->turn(60);
				}else if(!colorDetector->blackLineDetect()){
					driver->drive(60, 0);
				}else{
					closePhase = 2;
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 2:
				if(distance->getDiff() < 20 && !turnflag){
					if(runtime < 1000){
						driver->turn(-60);
					}else{
						driver->drive(-60, 0);
					}
				}else{
					if(turnflag){
						if(runtime < 500){
							driver->turn(10);
						}else{
							closePhase = 6;
							distance->init();
							driver->straightInit();
							runtime = 0;
							turnflag = false;
						}
					}else{
						turnflag = true;
						runtime = 0;
					}
				}
				break;
			case 6:
				lineTracer->changePid(0.15, 0.001, 0.055);
				lineTracer->lineTrace(25, RIGHTEDGE);
				if(distance->getDistance() < -80){
					closePhase = 7;
					driver->straight(0);	
					changePhase();
				}
				break;
			case 7:
				break;
		}
		break;

		case 3:
		st = true;
		driver->straightInit();
		driver->straight(0);
		break;
	}
	runtime += 4;
	return st;
}
