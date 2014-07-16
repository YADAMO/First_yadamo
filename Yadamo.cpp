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
#include "Speaker.h"

#include "Distance.h"
#include "TouchJudgement.h"
#include "UI.h"

using namespace ecrobot;

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define BLACK 591
#define WHITE 542

#define DRIVING_POWER		 70

#define STEER	PORT_C
#define DRIVE_L	PORT_A
#define DRIVE_R	PORT_B
#define LIGHT	PORT_3
#define TOUCH	PORT_2

TouchSensor touch(TOUCH);
Nxt nxt;
Clock clk;

Speaker speaker;
Motor motorL(DRIVE_L,true);
Motor motorR(DRIVE_R,true);
Motor motorS(STEER,true);
Driver driver(&motorL, &motorR, &motorS);
LightSensor light(LIGHT);
Pid pid(&light);
LineTracer lineTracer(&driver, &pid);
TouchJudgement touchJudgement(&touch);
UI ui(&light, &touchJudgement, &lineTracer, &clk, &speaker);


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

// Motor motorL(DRIVE_L,true);
// Motor motorR(DRIVE_R,true);
// Motor motorS(STEER,true);
// LightSensor light(LIGHT);
// TouchSensor touch(TOUCH);
// 	~nxt;
// 	~clk;

// 	~_line;
// 	~section;  
// 	~_driver;
// 	~_position;
// 	~_gray;
// 	~_pid;

}


/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

extern "C" TASK(OSEK_Task_Background)
{
	// int grey = (BLACK+WHITE)/2;
	// int light = 0;
	// int count = 0;
	motorL.setCount(0);
	motorR.setCount(0);

	ui.calibration();
	clk.wait(500); /* 500msec wait */	
	
	while(1)
	{
		lineTracer.lineTrace(10);
//		ecrobot_status_monitor("NXTrike Sample");
		display_clear(0);
		display_goto_xy(0,1);
		display_int(pid.calcTurn(light.getBrightness()), 1);
		display_int(light.getBrightness(), 3);
		display_update();
		clk.wait(4); /* 10msec wait */
	}
}