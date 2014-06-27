#include "Pid.h"
#include "math.h"
#include "LightSensor.h"

Pid::Pid(){
    delta = 0.001; //処理周期：現在1msec
    kp = 0.9;
    ki = 0.1;
    kd = 0.4;
    diff = {0,0};
    integral = 0;
}

int Pid::calcTurn(float target){
    float brightness = lightSensor.getBrightness();
    float p, i, d;
    
    diff[0] = diff[1];
    diff[1] = brightness - target;
    
    integral += (diff[1] + diff[0]) / 2.0 * delta;
    
    p = kp * diff[1];
    i = ki * integral;
    d = kd * (diff[1] - diff[0]) / delta;
    
    return math_limit(p + i + d, -100.0, 100.0);
}
