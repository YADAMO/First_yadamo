#pragma once
#include "LineTracer.h"
#include "Pid.h"
#include "Speaker.h"
#include "Distance.h"
#include "Motor.h"
#include "OffsetHolder.h"
#include "SpeedPid.h"

using namespace ecrobot;

class Basic{
private:
	LineTracer *lineTracer;
    Pid *pid;
    Speaker *speaker;
    Distance *distance;
    Motor *rightMotor;
    Motor *leftMotor;
    OffsetHolder *offsetHolder;
    SpeedPid *speedPid;
    int phase;
    int tmptarget;
    bool dflag;
public:
	Basic(LineTracer *lt, Pid *pd, Speaker *sp, Distance *dis, Motor *rm, Motor *lm, OffsetHolder *oh, SpeedPid *spid);
    ~Basic();
	bool runIN(void);
    bool runIN(int dammy);
    bool runToFigure(void);
    bool runToFigure(int dammy);
    bool runOUT(void);
    bool runToGrid(void);
    bool runToJump(void);
    bool runToGarage(void);
};
