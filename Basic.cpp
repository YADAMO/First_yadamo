#include "Basic.h"

#define IN_STRAIGHT_END -270
#define IN_SHARPCURVE_END -420
#define IN_SLOWCURVE_END -485
#define IN_LARGECURVE_END -770
#define IN_SHARPCURVE2_END -900
#define IN_CHANGEEDGE_END -920
#define IN_STRAIGHT2_1_END -980
#define IN_STRAIGHT2_END -1035
#define IN_SNAKEHEAD_END -1080
#define IN_SNAKECHEST_END -1180
#define IN_SNAKEBODY_END -1240
#define IN_SNAKEHIP_END -1300
#define IN_SNAKETAIL_END -1390
#define IN_STRAIGHT3_END -1665

#define IN_SHARPCURVE3_END -1820
#define IN_TOMOGUL_END -1920
#define IN_MOGULCURVE -2000

#define IN_RETURNLINE_END -50
#define IN_FRONTCURVE_END -175
#define IN_GATE3CURVE_END -300
#define IN_CHANGEEDGE2_END -320
#define IN_TOFIGURE_END -440

#define OUT_STRAIGHT_END -220
#define OUT_SHARPCURVE_END -380

#define OUT_SHARPCURVE2_END -130
#define OUT_STRAIGHT2_END -480
#define OUT_SHARPCURVE3_END -585

#define OUT_SHARPCURVE4_END -130
#define OUT_STRAIGHT3_END -425
#define OUT_TOJUMP_END -600

#define OUT_SHARPCURVE5_END -130
#define OUT_STRAIGHT4_END -365
#define OUT_AVOIDGRAY_END -445

Basic::Basic(LineTracer *lt, Pid *pd, Speaker *sp, Distance *dis, Motor *rm, Motor *lm, OffsetHolder *oh, SpeedPid *spid, Driver *dri){
	lineTracer = lt;
	pid = pd;
	speaker = sp;
	distance = dis;
	rightMotor = rm;
	leftMotor = lm;
	offsetHolder = oh;
	speedPid = spid;
	driver = dri;
	runtime = 0;
	phase = 0;
	tmptarget = 0;
	dflag = false;
}

Basic::~Basic(){
}

/*
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
			pid->changePid(0.28, 0.001, 0.036);
			lineTracer->lineTrace(90, RIGHTEDGE);
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
			pid->changePid(0.42, 0.001, 0.035);
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
			pid->changePid(0.36, 0.001, 0.025);
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
				lineTracer->setTarget((offsetHolder->getWhite()*3 + offsetHolder->getBlack()*2) / 5);
				phase++;
			}
			break;
		case 11:
			pid->changePid(0.4, 0.001, 0.035);
			lineTracer->lineTrace(60, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKETAIL_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
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
*/

bool Basic::runIN(int dammy){

	switch(phase){
		case 0:
			pid->changePid(0.15, 0.01, 0.058);
			lineTracer->lineTrace((float)35, RIGHTEDGE);
			if((distance->getDistance()) < IN_STRAIGHT_END){
				speaker->playTone(442, 500, 100);
				phase++;
				speedPid->resetIntegral(0.5);
			}
			break;
		case 1:			
			pid->changePid(0.28, 0.01, 0.058);
			lineTracer->lineTrace((float)23, RIGHTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite()* 3 + offsetHolder->getBlack() * 2) / 5);
				speedPid->resetIntegral(0.7);
			}
			break;

		case 2:
			pid->changePid(0.29, 0.01, 0.06);
			lineTracer->lineTrace((float)16, RIGHTEDGE);
			if((distance->getDistance()) < IN_SLOWCURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite()* 4 + offsetHolder->getBlack() * 2) / 6);
				speedPid->resetIntegral(0.8);
			}
			break;

		case 3:
			pid->changePid(0.22, 0.015, 0.055);
			lineTracer->lineTrace((float)26, RIGHTEDGE);
			if((distance->getDistance()) < IN_LARGECURVE_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				speedPid->resetIntegral(0.5);
			}
			break;

		case 4:
			pid->changePid(0.286, 0.01, 0.058);
			lineTracer->lineTrace((float)22, RIGHTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE2_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()*3) / 4);
				phase++;
				speedPid->resetIntegral(0.8);
			}
			break;

		case 5:
			pid->changePid(0.22, 0.001, 0.045);
			lineTracer->lineTrace((float)21, RIGHTEDGE);
			if((distance->getDistance()) < IN_CHANGEEDGE_END){
				speaker->playTone(442, 200, 100);
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				phase++;
			}
			break;

		case 6:
			pid->changePid(0.15, 0.001, 0.058);
			lineTracer->lineTrace((float)28, LEFTEDGE);
			if((distance->getDistance()) < IN_STRAIGHT2_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				speedPid->resetIntegral(0);
			}else if((distance->getDistance()) < IN_STRAIGHT2_1_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite()*3 + offsetHolder->getBlack()*2) / 5);
			}
			break;

		case 7:
			pid->changePid(0.43, 0.001, 0.035);
			lineTracer->lineTrace((float)9, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEHEAD_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;

		case 8:
			pid->changePid(0.31, 0.0015, 0.037);
			lineTracer->lineTrace((float)21, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKECHEST_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() * 3 + offsetHolder->getBlack() * 2) / 5);
				speedPid->resetIntegral(0.5);
			}
			break;

		case 9:
			pid->changePid(0.31, 0.001, 0.029);
			lineTracer->lineTrace((float)15, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEBODY_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
			}
			break;

		case 10:
			pid->changePid(0.285, 0.001, 0.035);
			lineTracer->lineTrace((float)22, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKEHIP_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite()*3 + offsetHolder->getBlack()*2) / 5);
				phase++;
			}
			break;
		case 11:
			pid->changePid(0.30, 0.001, 0.033);
			lineTracer->lineTrace((float)16, LEFTEDGE);
			if((distance->getDistance()) < IN_SNAKETAIL_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				phase++;
			}
			break;
		case 12:
			if(runtime < 0){
				driver->turn(-20);
				runtime += 3;
			}else{
				pid->changePid(0.15, 0.01, 0.058);
				lineTracer->lineTrace((float)35, LEFTEDGE);
				if((distance->getDistance()) < IN_STRAIGHT3_END){
					speaker->playTone(442, 500, 100);
					phase++;
					speedPid->resetIntegral(0);
				}
			}
			break;

		case 13:
			pid->changePid(0.35, 0.01, 0.058);
			lineTracer->lineTrace((float)18, LEFTEDGE);
			if((distance->getDistance()) < IN_SHARPCURVE3_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 14:
			pid->changePid(0.27, 0.001, 0.05);
			lineTracer->lineTrace((float)23, LEFTEDGE);
			if((distance->getDistance()) < IN_TOMOGUL_END){
				speaker->playTone(442, 500, 100);
				phase++;
				speedPid->resetIntegral(0.8);
			}
			break;
		case 15:
			pid->changePid(0.31, 0.001, 0.043);
			lineTracer->lineTrace((float)15, LEFTEDGE);
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
			lineTracer->lineTrace(30, LEFTEDGE);
			if((distance->getDistance()) < IN_RETURNLINE_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 1:
			pid->changePid(0.29, 0.001, 0.035);
			lineTracer->lineTrace(70, LEFTEDGE);
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

bool Basic::runOUT(void){
	switch(phase){
		case 0:
			pid->changePid(0.15, 0.01, 0.058);
			lineTracer->lineTrace((float)35, RIGHTEDGE);
			if((distance->getDistance()) < OUT_STRAIGHT_END){
				speaker->playTone(442, 500, 100);
				phase++;
				speedPid->resetIntegral(0.5);
			}
			break;
		case 1:
			pid->changePid(0.246, 0.001, 0.03);
			lineTracer->lineTrace((float)26, RIGHTEDGE);
			if((distance->getDistance()) < OUT_SHARPCURVE_END){
				speaker->playTone(442, 500, 100);
				speedPid->resetIntegral(0.5);
				phase++;
			}
			break;
		case 2:
			phase = 0;
			return true;
			break;
	}
	return false;
}

bool Basic::runToGrid(void){
	switch(phase){
		case 0:
			pid->changePid(0.245, 0.001, 0.03);
			lineTracer->lineTrace((float)24, RIGHTEDGE);
			if((distance->getDistance()) < OUT_SHARPCURVE2_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() * 4 + offsetHolder->getBlack() * 1) / 5);
			}
			break;
		case 1:
			pid->changePid(0.15, 0.01, 0.05);
			lineTracer->lineTrace((float)35, RIGHTEDGE);
			if((distance->getDistance()) < OUT_STRAIGHT2_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() + offsetHolder->getBlack()) / 2);
				speedPid->resetIntegral(0.2);
			}
			break;
		case 2:
			pid->changePid(0.26, 0.001, 0.038);
			lineTracer->lineTrace((float)17332, RIGHTEDGE);
			if((distance->getDistance()) < OUT_SHARPCURVE3_END){
				speaker->playTone(442, 500, 100);
				phase++;
			}
			break;
		case 3:
			phase = 0;
			return true;
			break;
	}
	return false;
}

bool Basic::runToJump(void){
	switch(phase){
		case 0:
			pid->changePid(0.24, 0.04, 0.03);
			lineTracer->lineTrace((float)23, RIGHTEDGE);
			if((distance->getDistance()) < OUT_SHARPCURVE4_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->resetIntegral(0);
			}
			break;
		case 1:
			pid->changePid(0.15, 0.001, 0.05);
			lineTracer->lineTrace((float)35, RIGHTEDGE);
			if((distance->getDistance()) < OUT_STRAIGHT3_END){
				speaker->playTone(442, 500, 100);
				phase++;
				speedPid->resetIntegral(0.5);
				lineTracer->resetIntegral(0.5);
			}
			break;
		case 2:
			pid->changePid(0.245, 0.001, 0.03);
			lineTracer->lineTrace((float)25, RIGHTEDGE);
			if((distance->getDistance()) < OUT_TOJUMP_END){
				speaker->playTone(442, 500, 100);
				phase++;
				speedPid->resetIntegral(0.5);
			}
			break;
		case 3:
			phase = 0;
			return true;
			break;
	}
	return false;
}

bool Basic::runToGarage(void){
	switch(phase){
		case 0:
			pid->changePid(0.245, 0.001, 0.03);
			lineTracer->lineTrace((float)24, RIGHTEDGE);
			if((distance->getDistance()) < OUT_SHARPCURVE5_END){
				speaker->playTone(442, 500, 100);
				phase++;
				// lineTracer->setTarget((offsetHolder->getWhite() * 3 + offsetHolder->getBlack()) / 4);
			}
			break;
		case 1:
			pid->changePid(0.15, 0.01, 0.05);
			lineTracer->lineTrace((float)35, RIGHTEDGE);
			if((distance->getDistance()) < OUT_STRAIGHT4_END){
				speaker->playTone(442, 500, 100);
				lineTracer->setTarget((offsetHolder->getWhite() * 3 + offsetHolder->getBlack()) / 4);
				phase++;
				speedPid->resetIntegral(0.6);
			}
			break;
		case 2:
			pid->changePid(0.15, 0.01, 0.05);
			lineTracer->lineTrace((float)25, RIGHTEDGE);
			if((distance->getDistance()) < OUT_AVOIDGRAY_END){
				speaker->playTone(442, 500, 100);
				phase++;
				lineTracer->setTarget((offsetHolder->getWhite() * 5 + offsetHolder->getBlack() * 6) / 11);
			}
			break;
		case 3:
			phase = 0;
			return true;
			break;
	}
	return false;
}

