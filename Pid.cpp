#include "Pid.h"
#include "math.h"

Pid::Pid(LightSensor *light){
    delta = 0.004; //処理周期：現在1msec
    kp = 0.6;
    ki = 0.1;
    kd = 0.4;
    diff[0] = 0;
	diff[1] = 0;
    integral = 0;
	lightSensor = light;
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



