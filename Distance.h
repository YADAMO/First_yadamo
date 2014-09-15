#pragma once
#include "Motor.h"

class Distance{
public:
	Distance();
	// Distance(S32 L, S32 R);
	~Distance();
	void init(S32 L, S32 R);
	F32 getDistance(S32 L, S32 R);
private:
	S32 leftOffset, rightOffset;
	S32 distanceL, distanceR;
	F32 distance;
};
