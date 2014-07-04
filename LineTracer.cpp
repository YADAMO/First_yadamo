#include "LineTracer.h"

LineTracer::LineTracer(Driver *argDriver, Pid *argPid)
{
  driver = argDriver;
  pid = argPid;
}

LineTracer::~LineTracer()
{

}

void LineTracer::lineTrace(int speed){
  driver->drive(pid->calcTurn(TARGET), speed);
}
