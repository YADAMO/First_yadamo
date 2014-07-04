#include "LineTracer.h"

LineTracer::LineTracer(Driver *argDriver)
{
  driver = argDriver;
}

LineTracer::~LineTracer()
{

}

void LineTracer::lineTrace(int speed){
  driver->drive(pid.calcTurn(570), speed);
}
