#include "GridRunner.h"

int scenario[] = {TURNLEFT, 0};//, GOSTRAIGHT, TURNRIGHT, GOSTRAIGHT, GOSTRAIGHT, GOSTRAIGHT};

GridRunner::GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd){
	lineTracer = lt;
	driver = dr;
	stepper = sp;
	colorDetector = cd;
//	scenario[15] = ;
	curScene = 0;
	detected = false;
	spFlag = true;
	runtime = 0;
}

GridRunner::~GridRunner(){

}

bool GridRunner::goStraight(){
	bool st = false;
	if(!detected){
		if(runtime < 2000){
		}else{
			if(colorDetector->blackLineDetect()){
				detected = true;
				driver->straightInit();
				runtime = 0;
			}
		}
		lineTracer->lineTrace(20, LEFTEDGE);
	}else{
		if(runtime < 1000){
			driver->straight(20);
		}else if(runtime < 2000){
			lineTracer->lineTrace(20, LEFTEDGE);
			driver->straightInit();
		}else if(runtime < 3000){
			driver->straight(0);
		}else{
			st = true;
			detected = false;
			runtime = 0;
		}
	}
	runtime += 4;
	return st;
}

bool GridRunner::turnRight(){
	bool st = false;
	if(!detected){
		if(runtime < 2000){
		}else{
			if(colorDetector->blackLineDetect()){
				detected = true;
				runtime = 0;
			}
		}
		lineTracer->lineTrace(20, LEFTEDGE);
	}else{
		if(runtime < 500){
			driver->drive(-100, 0);
		}else if(runtime < 1500){
			lineTracer->lineTrace(20, LEFTEDGE);
		}else if(runtime < 2500){
			driver->straight(0);
		}else{
			st = true;
			detected = false;
			runtime = 0;
		}
	}
	runtime += 4;
	return st;
}

bool GridRunner::turnLeft(){
	bool st = false;
	if(!detected){
		if(runtime < 1000){
		}else{
			if(colorDetector->blackLineDetect()){
				detected = true;
				runtime = 0;
				driver->straightInit();
			}
		}
		lineTracer->lineTrace(20, LEFTEDGE);
	}else{
		if(runtime < 1000){
			driver->straight(0);
		}else if(runtime < 2000){
			driver->straight(-20);
		}else if(runtime < 3000){
			driver->drive(40, 40);
			driver->straightInit();
		}else if(runtime < 4000){
			driver->straight(0);
		}else if(runtime < 5500){
			lineTracer->lineTrace(20, LEFTEDGE);
			driver->straightInit();
		}else if(runtime < 7000){
			driver->straight(0);
		}else{
			st = true;
			detected = false;
			runtime = 0;
		}
	}
	runtime += 4;
	return st;
}

bool GridRunner::run(){
	bool st = false;
	if(!spFlag){
		if(stepper->run(RIGHTEDGE)){
			spFlag = true;
		}
	}else{
		switch(scenario[curScene]){
			case GOSTRAIGHT:
			if(goStraight()){
				curScene++;
			}
			break;

			case TURNRIGHT:
			if(turnRight()){
				curScene++;
			}
			break;

			case TURNLEFT:
			if(turnLeft()){
				curScene++;
			}
			break;

			case 0:
			driver->straight(0);
			st = true;
			break;
		}
	}
	return st;
}
