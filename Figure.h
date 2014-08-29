#pragma once
#include "LineTracer.h"

using namespace ecrobot;

class Figure{
private:
	LineTracer *lineTracer;
	int runtime;
public:
	Figure(LineTracer *argLineTracer);
	~Figure();
	bool run();
};
