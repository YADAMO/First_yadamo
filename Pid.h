#pragma once

class Pid{
private:
    int p;
    int i;
    int d;
    int diff[5];
public:
	Pid();
    int calcTurn(int brighitness);
};
