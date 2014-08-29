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
	void OffsetHolder::setBlack(S16 value);
	S16 OffsetHolder::getBlack();
	void OffsetHolder::setWhite(S16 value);
	S16 OffsetHolder::getWhite();
};
