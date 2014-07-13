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

void LineTracer::lineTrace(int speed){
  driver->drive(pid->calcTurn(target), speed);
}

void LineTracer::setTarget(float tar){
  target = tar;
}

void LineTracer::setTARGET(float target){
	TARGET = target;
}
