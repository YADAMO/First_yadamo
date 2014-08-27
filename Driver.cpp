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


void Driver::operate(int leftStickValue, int rightStickValue){
	//rightStickValue is steer value(left:-100 ~ right:100)
	//left is speed(-100 ~ 100)
	int count = motorS->getCount();
	
	int maxAngle = rightStickValue * 3;
	
	if(maxAngle >= 7){
		if(count < maxAngle)
			motorS->setPWM(100);
		else
			motorS->setPWM(-100);
	}else if(maxAngle <= 7){
		if(count > maxAngle)
			motorS->setPWM(-100);
		else
			motorS->setPWM(100);
	}else{
		motorS->setPWM(0);
	}
	
	int speedR = (leftStickValue + (leftStickValue > 0 ? -1*rightStickValue/2 :    rightStickValue/2))*1.5;
	int speedL = (leftStickValue + (leftStickValue > 0 ?    rightStickValue/2 : -1*rightStickValue/2))*1.5;
	if(speedR > 127) speedR = 127;
	else if(speedR < -128) speedR = -128;
	if(speedL > 127) speedR = 127;
	else if(speedL < -128) speedL = -128;
	
	motorR->setPWM(speedR);
	motorL->setPWM(speedL);
}


