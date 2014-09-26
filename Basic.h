#pragma once
#include "LineTracer.h"
#include "Pid.h"
#include "Speaker.h"
#include "Distance.h"
#include "Motor.h"
#include "OffsetHolder.h"

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
    int phase;
    int tmptarget;
    bool dflag;
public:
	Basic(LineTracer *lt, Pid *pd, Speaker *sp, Distance *dis, Motor *rm, Motor *lm, OffsetHolder *oh);
    ~Basic();
	bool runIN(void);
    bool runToFigure(void);
    bool runOUT(void);
    bool runToGrid(void);
    bool runToJump(void);
    bool runToGarage(void);
};
