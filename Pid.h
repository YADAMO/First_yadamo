#pragma once

class Pid{
private:
    float delta;
    float kp;
    float ki;
    float kd;
    float diff[2];
    float integral;
public:
	Pid();
    int calcTurn(int brighitness);
};
