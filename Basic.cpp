#include "Basic.h"

#define IN_STRAIGHT_END -270
#define IN_SHARPCURVE_END -420
#define IN_SLOWCURVE_END -490
#define IN_LARGECURVE_END -770
#define IN_SHARPCURVE2_END -900
#define IN_CHANGEEDGE_END -920
#define IN_STRAIGHT2_END -1035
#define IN_SNAKEHEAD_END -1080
#define IN_SNAKECHEST_END -1180
#define IN_SNAKEBODY_END -1240
#define IN_SNAKEHIP_END -1300
#define IN_SNAKETAIL_END -1380
#define IN_STRAIGHT3_END -1670

#define IN_SHARPCURVE3_END -1820
#define IN_TOMOGUL_END -1920
#define IN_MOGULCURVE -2000

#define IN_RETURNLINE_END -65
#define IN_FRONTCURVE_END -175
#define IN_GATE3CURVE_END -300
#define IN_CHANGEEDGE2_END -320
#define IN_TOFIGURE_END -440

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
	dflag = false;
}

Basic::~Basic(){
}

bool Basic::runIN(void){

	switch(phase){
		case 0:
			pid->changePid(0.25, 0.001, 0.058);
			lineTracer->lineTrace(110, RIGHTEDGE);
			if((distance->getDistance()) < IN_STRAIGHT_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 1:
			pid->changePid(0.286, 0.001, 0.03);
			lineTracer->lineTrace(70, RIGHTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 2:
			pid->changePid(0.286, 0.001, 0.03);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance()) < IN_SLOWCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 3:
			pid->changePid(0.27, 0.001, 0.045);
			lineTracer->lineTrace(85, RIGHTEDGE);
			if((distance->getDistance()) < IN_LARGECURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 4:
			pid->changePid(0.29, 0.001, 0.03);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE2_END){
				speaker->playTone(442, 500, 100);
				tmptarget = lineTracer->getTarget();
				lineTracer->setTarget((tmptarget + offsetHolder->getBlack() * 3) / 4);
				phase++;
			}
			break;

		case 5:
			pid->changePid(0.22, 0.001, 0.045);
			lineTracer->lineTrace(65, RIGHTEDGE);
			if((distance->getDistance()) < IN_CHANGEEDGE_END){
				speaker->playTone(442, 500, 100);
				tmptarget = lineTracer->getTarget();
				lineTracer->setTarget((tmptarget * 2 + offsetHolder->getWhite() * 3) / 5);
				phase++;
			}
			break;

		case 6:
			pid->changePid(0.22, 0.001, 0.058);
			lineTracer->lineTrace(90, LEFTEDGE);
			if((distance->getDistance()) < IN_STRAIGHT2_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
			}
			break;

		case 7:
			pid->changePid(0.4, 0.001, 0.035);
			lineTracer->lineTrace(30, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEHEAD_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 8:
			pid->changePid(0.295, 0.001, 0.035);
			lineTracer->lineTrace(70, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKECHEST_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() * 3 + offsetHolder->getBlack() * 2) / 5);
			}
			break;

		case 9:
			pid->changePid(0.35, 0.001, 0.035);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEBODY_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
			}
			break;

		case 10:
			pid->changePid(0.285, 0.001, 0.035);
			lineTracer->lineTrace(80, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEHIP_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 11:
			pid->changePid(0.315, 0.001, 0.03);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKETAIL_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 12:
			pid->changePid(0.2, 0.001, 0.058);
			lineTracer->lineTrace(110, LEFTEDGE);
			if((distance->getDistance()) < IN_STRAIGHT3_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 13:
			pid->changePid(0.32, 0.001, 0.04);
			lineTracer->lineTrace(70, LEFTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE3_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 14:
			pid->changePid(0.27, 0.001, 0.05);
			lineTracer->lineTrace(85, LEFTEDGE);
			if((distance->getDistance()) < IN_TOMOGUL_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 15:
			pid->changePid(0.31, 0.001, 0.043);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance()) < IN_MOGULCURVE){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 16:
			phase = 0;
			return true;
			break;
	}
	return false;
}

bool Basic::runToFigure(void){
	if(!dflag){
		distance->init();
		dflag = true;
	}
	switch(phase){
		case 0:
			pid->changePid(0.15, 0.001, 0.02);
			lineTracer->lineTrace(40, LEFTEDGE);
			if((distance->getDistance()) < IN_RETURNLINE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 1:
			pid->changePid(0.29, 0.001, 0.035);
			lineTracer->lineTrace(80, LEFTEDGE);
			if((distance->getDistance()) < IN_FRONTCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 2:
			pid->changePid(0.32, 0.001, 0.04);
			lineTracer->lineTrace(70, LEFTEDGE);
			if((distance->getDistance()) < IN_GATE3CURVE_END){
				speaker->playTone(442, 500, 100);
				tmptarget = lineTracer->getTarget();
				lineTracer->setTarget((tmptarget + offsetHolder->getBlack() * 3) / 4);
				phase++;
			}
			break;
		case 3:
			pid->changePid(0.22, 0.001, 0.045);
			lineTracer->lineTrace(65, LEFTEDGE);
			if((distance->getDistance()) < IN_CHANGEEDGE2_END){
				speaker->playTone(442, 500, 100);
				tmptarget = lineTracer->getTarget();
				lineTracer->setTarget((tmptarget * 2 + offsetHolder->getWhite() * 3) / 5);
				phase++;
			}
			break;
		case 4:
			pid->changePid(0.22, 0.001, 0.058);
			lineTracer->lineTrace(90, RIGHTEDGE);
			if((distance->getDistance()) < IN_TOFIGURE_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				phase++;
			}
			break;
		case 5:
			pid->changePid(0.22, 0.001, 0.05);
			phase = 0;
			return true;
			break;
	}
	return false;
}

