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
    if(runtime < 56){
    	runtime += 4;
    }else{
    	runtime = 0;
    }
   	buffer[runtime/4] = lightSensor->getBrightness();

    int sum = 0;
    for(int i = 0; i < 15; i++){
    	sum += (int)buffer[i];
    }


    if(buffer[0] < oHolder->getBlack() + 10){
    	return true;
    }else{
    	return false;
    }
}
