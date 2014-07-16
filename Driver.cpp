#include "Driver.h"

Driver::Driver(Motor *L, Motor *R, Motor *S){
  motorL = L;
  motorR = R;
  motorS = S;
}

Driver::~Driver(){

}


void Driver::drive(int turn, int speed){
  int count = motorS->getCount();
  int right, left;

  if(turn > 0){
    if(count>-MAX_STEERING_ANGLE){
      motorS->setPWM(-100);
    }else{
      motorS->setPWM(0);
    }
  }else if(turn < 0){
    if(count<MAX_STEERING_ANGLE){
      motorS->setPWM(100);
    }else{
      motorS->setPWM(0);
    }
  }else{
    if(count > 0){
      motorS->setPWM(-100);
    }else if(count < 0){
      motorS->setPWM(100);
    }else{
      motorS->setPWM(0);
    }
  }
  
  right = -turn/2 - speed;
  left = turn/2 - speed;
  if(right >= 127)	right = 127;
  if(right <= -128)	right = -128;
  if(left >= 127)	left = 127;
  if(left <= -128)	left = -128;
  
  motorL->setPWM(left);
  motorR->setPWM(right);
}

void Driver::turn(int angle){
  /*
    モーターエンコード値と旋回角度の相関を計算してください
  */
}

void Driver::driveStraight(int distance){
  /*
    モーターエンコード値と距離の相関を計算してください
  */
}
