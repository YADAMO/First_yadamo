#define once
//read neccessary header file
//#include header file of Motor class
#include  "LineTracer.h"

class Driver {
private:
public:
  Driver();
  ~Driver();   
  void drive(int turn, int speed); 
  void turn(int angle);
  void driveStraight(int distance);
};
