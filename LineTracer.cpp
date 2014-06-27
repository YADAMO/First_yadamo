#include "LineTracer.h"

LineTracer::LineTracer()
{

}

LineTracer::~LineTracer()
{

}

void LineTracer::lineTrace(int speed){
  driver.drive(calcTurn(float brightness, 570), speed);
}
