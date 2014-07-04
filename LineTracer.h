#pragma once
//read neccessary header file
//#include header file of PID class
#include "Driver.h"
#include "SectionController.h"
#include "Pid.h"

class LineTracer {
private:
//not define on UML
  Driver *driver;
  Pid pid;
public:
	LineTracer(Driver *argDriver);
	~LineTracer();		
  void lineTrace(int speed);
};
