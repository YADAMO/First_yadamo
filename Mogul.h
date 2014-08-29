#pragma once

#include "Motor.h"

class Mogul{
private:
	Motor *rightMotor;
	Motor *leftMotor;

public:
	Mogul(Motor *rightMotor,);
	bool run();
}