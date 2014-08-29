#include "Figure.h"

Figure::Figure(LineTracer *argLineTracer){
	lineTracer = argLineTracer;
	runtime = 0;
}

Figure::~Figure(){
}

bool Figure::run(){
	if(runtime < 1000)
		lineTracer->lineTrace(40, LEFT);
	else
		lineTracer->lineTrace(20, LEFT);
		
	runtime += 4;
	return true;
}
