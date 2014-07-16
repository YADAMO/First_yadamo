#include "Pid.h"

Pid::Pid(LightSensor *light){
    delta = 0.004; //処理周期：現在1msec
    kp = 0.3;
    ki = 0.001;
    kd = 0.03;
    diff[0] = 0;
	diff[1] = 0;
    integral = 0;
	lightSensor = light;
}

void Pid::changePid(float p, float i, float d){
	if((p < 0) || (i < 0) || (d < 0)){
		return;
	}
	
	kp = p;
	ki = i;
	kd = d;
}

int Pid::calcTurn(float target){
    float brightness = lightSensor->getBrightness();
    float p, i, d;
    int turn;
    diff[0] = diff[1];
    diff[1] = brightness - target;
    
    integral += (diff[1] + diff[0]) / 2.0 * delta;
    
    p = kp * diff[1];
    i = ki * integral;
    d = kd * (diff[1] - diff[0]) / delta;
	
	turn = (int)(p + i + d);
	if(turn <= -100){
	  turn = -100;
	}else if(turn >= 100){
	  turn = 100;
	}
	
    return  turn;
}



