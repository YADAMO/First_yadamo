#pragma once
#include "LightSensor.h"

using namespace ecrobot;

#define BRIGHT_PLACE  FALSE
#define DARK_PLACE TRUE

class OffsetHolder{
private:
	S16 black_bright;
	S16 white_bright;
	S16 black_dark;
	S16 white_dark;
public:
	OffsetHolder();
	~OffsetHolder();
	void setBlack(S16 value,bool place);
	S16 getBlack(bool place);
	S16 getBlack();
	void setWhite(S16 value,bool place);
	S16 getWhite(bool place);
	S16 getWhite();
};
