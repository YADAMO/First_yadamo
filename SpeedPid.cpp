#include "SpeedPid.h"

SpeedPid::SpeedPid(SpeedMeter *sm){
    delta = 0.004; //処理周期：現在1msec

    kp = 5; //ストレート
    ki = 20;//ストレート
    kd = 0.05;//ストレート

    diff[0] = 0;
	diff[1] = 0;
    integral = 0;
	speedMeter = sm;
    speedbuf = 50;
}

void SpeedPid::changePid(float p, float i, float d){
	if((p < 0) || (i < 0) || (d < 0)){
		return;
	}
	
	kp = p;
	ki = i;
	kd = d;
}

int SpeedPid::calcSpeed(float target){
    float sp = speedMeter->getSpeed();
    float p, i, d;
    int speed;
    diff[0] = diff[1];
    diff[1] = target - sp;
    
    integral += (diff[1] + diff[0]) / 2.0 * delta;
    
    p = kp * diff[1];
    i = ki * integral;
    d = kd * (diff[1] - diff[0]) / delta;
	
	speed = (int)(p + i + d);
	
    if(speed < -100){
        speed = -100;
    }
    if(speed > 115){
        speed = 110;
    }

    if((speed - speedbuf) < -30){
        speed = speedbuf - 5;
    }
    speedbuf = speed;
    return  speed;
}



