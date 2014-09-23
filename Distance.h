#pragma once
#include "Motor.h"
using namespace ecrobot;
class Distance{
private:
	Motor *motorR;
	Motor *motorL;
	S32 leftOffset, rightOffset;
	S32 distanceL, distanceR;
	F32 distance;
public:
	Distance(Motor *rm, Motor *lm);
	~Distance();
	void init();
	F32 getDistance();
	int getDiff();
};
