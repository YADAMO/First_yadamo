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

  if(turn > 0){
    if(count>-MAX_STEERING_ANGLE){
      // motorS->setPWM(-100);
    }else{
      // motorS->setPWM(0);
    }
  }else if(turn < 0){
    if(count<MAX_STEERING_ANGLE){
      // motorS->setPWM(100);
    }else{
      // motorS->setPWM(0);
    }
  }else{
    if(count > 0){
      // motorS->setPWM(-100);
    }else if(count < 0){
      // motorS->setPWM(100);
    }else{
      // motorS->setPWM(0);
    }
  }
  motorL->setPWM(turn + speed);
  motorR->setPWM(-turn + speed);
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
