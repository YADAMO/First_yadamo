#include "Basic.h"

#define IN_STRAIGHT_END -270
#define IN_SHARPCURVE_END -420
#define IN_SLOWCURVE_END -490
#define IN_LARGECURVE_END -770
#define IN_SHARPCURVE2_END -900
#define IN_CHANGEEDGE_END -920
#define IN_STRAIGHT2_END -1035
#define IN_SNAKEHEAD_END -1110
#define IN_SNAKECHEST_END -1180
#define IN_SNAKEBODY_END -1240
#define IN_SNAKETAIL_END -1380
#define IN_STRAIGHT3_END -1670

Basic::Basic(LineTracer *lt, Pid *pd, Speaker *sp, Distance *dis, Motor *rm, Motor *lm, OffsetHolder *oh){
	lineTracer = lt;
	pid = pd;
	speaker = sp;
	distance = dis;
	rightMotor = rm;
	leftMotor = lm;
	offsetHolder = oh;
	phase = 0;
	tmptarget = 0;
}

Basic::~Basic(){
}

bool Basic::runIN(void){

	switch(phase){
		case 0:
			pid->changePid(0.2, 0.001, 0.058);
			lineTracer->lineTrace(110, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_STRAIGHT_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 1:
			pid->changePid(0.286, 0.001, 0.03);
			lineTracer->lineTrace(70, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SHARPCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 2:
			pid->changePid(0.286, 0.001, 0.03);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SLOWCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 3:
			pid->changePid(0.27, 0.001, 0.05);
			lineTracer->lineTrace(85, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_LARGECURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 4:
			pid->changePid(0.29, 0.001, 0.03);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SHARPCURVE2_END){
				speaker->playTone(442, 500, 100);
				tmptarget = lineTracer->getTarget();
				lineTracer->setTarget((tmptarget + offsetHolder->getBlack() * 3) / 4);
				phase++;
			}
			break;

		case 5:
			pid->changePid(0.22, 0.001, 0.045);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_CHANGEEDGE_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget(tmptarget);
				phase++;
			}
			break;

		case 6:
			pid->changePid(0.22, 0.001, 0.058);
			lineTracer->lineTrace(70, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_STRAIGHT2_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 7:
			pid->changePid(0.4, 0.001, 0.035);
			lineTracer->lineTrace(30, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SNAKEHEAD_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 8:
			pid->changePid(0.3, 0.001, 0.03);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SNAKECHEST_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 9:
			pid->changePid(0.35, 0.001, 0.03);
			lineTracer->lineTrace(30, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SNAKEBODY_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 10:
			pid->changePid(0.3, 0.001, 0.03);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_SNAKETAIL_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 11:
			pid->changePid(0.2, 0.001, 0.058);
			lineTracer->lineTrace(110, LEFTEDGE);
			if((distance->getDistance(leftMotor->getCount(), rightMotor->getCount())) < IN_STRAIGHT3_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 12:
			return true;
			break;
	}
	return false;
}
