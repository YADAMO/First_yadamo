#include "LineTracer.h"

LineTracer::LineTracer(Driver *argDriver, Pid *argPid)
{
  driver = argDriver;
  pid = argPid;
  target = 600;
}

LineTracer::~LineTracer()
{

}

//hidari adge == 1 , migi adge == -1
void LineTracer::lineTrace(int speed, int adge){
  driver->drive(adge * pid->calcTurn(target), speed);
}

void LineTracer::setTarget(float tar){
	target = tar;
}

float LineTracer::getTarget(){
	return target;
}
