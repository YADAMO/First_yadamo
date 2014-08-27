#include "UI.h"

UI::UI(LightSensor *light, TouchJudgement *touchJ, LineTracer *lineT, Clock *clk, Speaker *spk){
	lightSensor = light;
	touchJudgement = touchJ;
	lineTracer = lineT;
	clock = clk;
	speaker = spk;
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
				speaker->playTone(442, 100, 10);
				judge = false;
			}else if(touchCount == 2){
				black = lightSensor->getBrightness();
				speaker->playTone(884, 100, 10);
				judge = false;
			}else if(touchCount == 3){
				lineTracer->setTarget(((float)white + (float)black) / 2);
				speaker->playTone(1326, 100, 10);
				judge = false;
				break;
			}
		}
		clock->wait(10);
	}
	
}

