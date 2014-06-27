#include "Driver.h"

Driver::Driver(){

}

Driver::~Driver(){

}


void drive(int turn, int speed){
  int count = motorS.getCount();

  if(turn > 0){
    if(count>-MAX_STEERING_ANGLE){
      motorS.setPWM(-100);
    }else{
      motorS.setPWM(0);
    }
  }else if(turn < 0){
    if(count<MAX_STEERING_ANGLE){
      motorS.setPWM(100);
    }else{
      motorS.setPWM(0);
    }
  }else{
    if(count > 0){
      motorS.setPWM(-100);
    }else if(count < 0){
      motorS.setPWM(100);
    }else{
      motorS.setPWM(0);
    }
  }
  motorL.setPWM(turn + speed);
  motorR.setPWM(-turn + speed);
}

void turn(int angle){
  /*
    モーターエンコード値と旋回角度の相関を計算してください
  */
}

void driveStraight(int distance){
  /*
    モーターエンコード値と距離の相関を計算してください
  */
}
