#pragma once

#define GOSTRAIGHT 1
#define TURN 2
#define UNUSED_VARIABLE(x) (void)(x) //warning消し

class RunPattern{
private:
public:
	RunPattern(){
		int pattern = 0;
		int param = 0;
		int angle = 0;
		UNUSED_VARIABLE(pattern);
		UNUSED_VARIABLE(param);
		UNUSED_VARIABLE(angle);
	}
	RunPattern(int pat, int prm, int ang){
		int pattern = pat;
		int param = prm;
		int angle = ang;
		UNUSED_VARIABLE(pattern);
		UNUSED_VARIABLE(param);
		UNUSED_VARIABLE(angle);
	}
	~RunPattern(){
	}
	int pattern;
	int param;
	int angle;
};
