#include "Mogul.h"

Mogul::Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *sp){
	driver = dr;
	lineTracer = lt;
	stepDetector = sd;
	stepper = sp;
	phase = 0;
	runtime = 0;
	hillnum = 0;
	sflag = false;
}

Mogul::~Mogul(){

}

bool Mogul::run(){
	runtime += 4;
	switch(phase){
		case 0://段差に上る
			if(stepper->run(-1)){
				phase++;
				runtime = 0;
			}
			break;

		case 1://１秒止まる
			driver->straight(0);
			if(runtime > 1000){
				phase++;
				runtime = 0;
			}
			break;

		case 2://
			lineTracer->lineTrace(40, -1);
			if(runtime > 1000){
				phase++;
				runtime = 0;
			}
			break;
		case 3://
			driver->straight(40);
			if(runtime > 1200){
				phase++;
				runtime = 0;
			}
			break;
		case 4:
			driver->straight(0);
			if(runtime > 2000){
				phase++;
				runtime = 0;
			}
			break;
		case 5:
			lineTracer->lineTrace(20, -1);
			break;

	}
	return false;
}
