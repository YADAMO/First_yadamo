#include "LineTracer.h"

LineTracer::LineTracer()
{

}

LineTracer::~LineTracer()
{

}		

void lineTrace(int speed){
  driver.drive(calcTurn(), speed);
}
