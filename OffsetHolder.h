#pragma once
#include "LightSensor.h"

using namespace ecrobot;

class OffsetHolder{
private:
	S16 black;
	S16 white;
public:
	OffsetHolder();
	~OffsetHolder();
	void setBlack(S16 value);
	S16 getBlack();
	void setWhite(S16 value);
	S16 getWhite();
};
