#include "Driver.h"

Driver::Driver(Motor *L, Motor *R, Motor *S){
  motorL = L;
  motorR = R;
  motorS = S;
  rightOffset = 0;
  leftOffset = 0;
}

Driver::~Driver(){

}

int Driver::calcSteerAngle(S8 right, S8 left){
  int angle = right - left;
  if(angle >= 127)  angle = 127;
  if(angle <= -128) angle = -128;

  return angle*4;
}

void Driver::drive(int turn, int speed){
  int count = motorS->getCount();
  steerAngle = 0;
  int right, left;
  
  right = -turn/1.5 - speed;
  left = turn/1.5 - speed;
  if(right >= 127)	right = 127;
  if(right <= -128)	right = -128;
  if(left >= 127)	left = 127;
  if(left <= -128)	left = -128;
  
  motorL->setPWM(left);
  motorR->setPWM(right);

  steerAngle = calcSteerAngle(right, left);

  if(turn > 0){
    if(count > steerAngle){
      motorS->setPWM(-turn - TURN_BASE_SPEED);
    }else{
      motorS->setPWM(0);
    }
  }else if(turn < 0){
    if(count < steerAngle){
      motorS->setPWM(-turn + TURN_BASE_SPEED);
    }else{
      motorS->setPWM(0);
    }
  }else{
    if(count > 0){
      motorS->setPWM(-turn - TURN_BASE_SPEED);
    }else if(count < 0){
      motorS->setPWM(-turn + TURN_BASE_SPEED);
    }else{
      motorS->setPWM(0);
    }
  }
}

void Driver::turn(int angle){
  /*
    モーターエンコード値と旋回角度の相関を計算してください
  */
}

void Driver::straightInit(){
	rightOffset = motorR->getCount();
	leftOffset = motorL->getCount();
}

void Driver::straight(int speed){
	int turn = (motorR->getCount() - rightOffset) - (motorL->getCount() - leftOffset);
	
	int right = -turn/2 - speed;
	int left = turn/2 - speed;
	if(right >= 127)	right = 127;
	if(right <= -128)	right = -128;
	if(left >= 127)	left = 127;
	if(left <= -128)	left = -128;
  
	motorL->setPWM(left);
	motorR->setPWM(right);
	
}


