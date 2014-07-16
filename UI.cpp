#include "UI.h"

UI::UI(LightSensor *light, TouchJudgement *touchJ, LineTracer *lineT, Clock *clk){
	lightSensor = light;
	touchJudgement = touchJ;
	lineTracer = lineT;
	clock = clk;
	touchCount = 0;
	judge = false;
	white = 0;
	black = 0;
}

UI::~UI(){

}

void UI::calibration(void){

	while(true){
		judge = touchJudgement->judge();
		if(judge){
			touchCount++;
			if(touchCount == 1){
				white = lightSensor->getBrightness();
				judge = false;
			}else if(touchCount == 2){
				black = lightSensor->getBrightness();
				judge = false;
			}else if(touchCount == 3){
				lineTracer->setTarget(((float)white + (float)black) / 2);
				judge = false;
				break;
			}
		}
		clock->wait(10);
	}
	
}

