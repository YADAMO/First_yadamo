/*
 * NXTrikeβ2～3(ETR100b2/b3) firmware
 *
 * NXTrikeSample.c for TOPPERS/ATK(OSEK)
 * 2013.11.27 TANAHASHI, Jiro
 */

#include "LineTracer.h"
#include "SectionController.h"
#include "Driver.h"
#include "PositionEstimater.h"
#include "GrayDetector.h"
#include "Pid.h"

#include "Motor.h"
#include "Port.h" //difined enum of port
#include "Clock.h"
#include "GyroSensor.h"
#include "LightSensor.h"
#include "TouchSensor.h"
#include "Nxt.h"
#include "Bluetooth.h"
#include "Daq.h"

using namespace ecrobot;

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define BLACK 591
#define WHITE 542

#define MAX_STEERING_ANGLE	270
#define DRIVING_POWER		 70

#define STEER	PORT_C
#define DRIVE_L	PORT_A
#define DRIVE_R	PORT_B
#define LIGHT	PORT_3
#define TOUCH	PORT_2

Motor _motorL(DRIVE_L,true);
Motor _motorR(DRIVE_R,true);
Motor _motorS(STEER,true);
LightSensor _light(LIGHT);
TouchSensor _touch(TOUCH);
Nxt _nxt;
Clock _clk;

// LineTracer _line;
// SectionController section;  
// Driver _driver;
// PositionEstimater _position;
// GrayDetector _gray;
// Pid _pid;

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{

}

void ecrobot_device_terminate()
{

// Motor _motorL(DRIVE_L,true);
// Motor _motorR(DRIVE_R,true);
// Motor _motorS(STEER,true);
// LightSensor _light(LIGHT);
// TouchSensor _touch(TOUCH);
// 	~_nxt;
// 	~_clk;

// 	~_line;
// 	~section;  
// 	~_driver;
// 	~_position;
// 	~_gray;
// 	~_pid;

}


/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	int grey = (BLACK+WHITE)/2;
	int light = 0;
	int count = 0;
	int cnt = 0;
	int cnt_2 = 0;
	_motorL.setCount(0);
	_motorR.setCount(0);

	while(!touch.isPressed());
		_clk.wait(500); /* 500msec wait */
	
	while(1)
	{
		light = _light.get();
		count = _motorS.getCount();
		cnt ++;
		if(light<grey){
			if(count<MAX_STEERING_ANGLE){
				_motorS.setPWM(100);
			}else{
				_motorS.setPWM(0);
			}
			_motorL.setPWM(-DRIVING_POWER);
			_motorR.setPWM(1);
		}else{
			if(count>-MAX_STEERING_ANGLE){
				_motorS.setPWM(-100);
			}else{
				_motorS.setPWM(0);
			}
			_motorL.setPWM(1);
			_motorR.setPWM(-DRIVING_POWER);
		}

  		ecrobot_status_monitor("NXTrike Sample");
		_clk.wait(10); /* 10msec wait */
	}
}

