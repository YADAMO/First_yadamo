#include "ColorDetector.h"

ColorDetector::ColorDetector(LightSensor *argLightSensor, OffsetHolder *oH){
    // threshold = 0;
    // buffer = 0;
    lightSensor = argLightSensor;
    oHolder = oH;

    runtime = 0;
}

bool ColorDetector::grayDetect(){
    // bool isGray;
    
    // return isGray;
    return true;
}

bool ColorDetector::blackLineDetect(){
    if(runtime < 60){
    	buffer[runtime/4] = lightSensor->getBrightness();
    }

    int sum = 0;
    for(int i = 0; i < 15; i++){
    	sum += (int)buffer[i];
    }

    runtime += 4;

    if(sum / 15 < oHolder->getBlack() + 20){
    	return true;
    }else{
    	return false;
    }
}
