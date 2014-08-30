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
#include "ColorDetector.h"
#include "Pid.h"
#include "ReturnLine.h"
#include "Figure.h"
#include "OffsetHolder.h"

#include "Motor.h"
#include "Port.h" //difined enum of port
#include "Clock.h"
#include "GyroSensor.h"
#include "LightSensor.h"
#include "TouchSensor.h"
#include "Nxt.h"
#include "BtConnection.h"
#include "GamePad.h"
#include "Bluetooth.h"
#include "Lcd.h"
#include "Daq.h"
#include "Speaker.h"

#include "Distance.h"
#include "TouchJudgement.h"
#include "UI.h"
#include "StepDetector.h"
#include "Mogul.h"
#include "Stepper.h"
#include "Jumper.h"

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

Bluetooth bt;
static const CHAR* PASSKEY = "YADAMO";

TouchSensor touch(TOUCH);
Nxt nxt;
Clock clk;

OffsetHolder oHolder;
SectionController sectionController;
Speaker speaker;
Motor motorL(DRIVE_L,true);
Motor motorR(DRIVE_R,true);
Motor motorS(STEER,true);
Driver driver(&motorL, &motorR, &motorS);
LightSensor light(LIGHT);
Pid pid(&light);
LineTracer lineTracer(&driver, &pid);
TouchJudgement touchJudgement(&touch);
ColorDetector colorDetector(&light, &oHolder);
Figure figure(&lineTracer, &colorDetector, &driver);
UI ui(&light, &touchJudgement, &lineTracer, &clk, &speaker, &oHolder);
ReturnLine returnLine(&driver, &light, &colorDetector);
StepDetector stepDetector(&motorR, &motorL, &speaker);
Stepper stepper(&stepDetector, &lineTracer, &driver);
Mogul mogul(&driver, &lineTracer, &stepDetector, &stepper);
Jumper jumper(&driver, &lineTracer, &stepper);


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
	Lcd lcd;
	BTConnection btConnection(bt, lcd, nxt);
	
	bool btConnected = false;
	if (btConnection.connect(PASSKEY) == 1)
		btConnected = true;
		
	speaker.playTone(442, 100, 10);
	
	// int grey = (BLACK+WHITE)/2;
	// int light = 0;
	// int count = 0;
	motorL.setCount(0);
	motorR.setCount(0);
	

	ui.calibration();
	clk.wait(500); /* 500msec wait */
	
	GamePad gp(bt);
	Daq daq(bt);
	VectorT<S8> command;
	
	int offsetmX;
	int offsetmY;
	
	if (btConnected)
	{
		command = gp.get();
		lcd.clear();
		lcd.putf("s", (gp.isConnected() ? "connected": "not connected"));
		offsetmX = command.mX;
		offsetmY = command.mY;
	}
	
	int hoseimX;
	int hoseimY;
	
	S8 logToDataC[2];
	logToDataC[0] = 1;
	logToDataC[1] = 2;
	U16 logToBatteryC = 3;
	S16 logToAdcC[4];
	logToAdcC[0] = 4;
	logToAdcC[1] = 5;
	logToAdcC[2] = 6;
	logToAdcC[3] = 7;

	S32 logToMotorrevC[4];
	logToMotorrevC[0] = 8;
	logToMotorrevC[1] = 9;
	logToMotorrevC[2] = 10;
	logToMotorrevC[3] = 11;	
	
	int runtime = 0;
	int phase = 0;
	while(1)
	{
		
//		driver.operate(hoseimX, hoseimY);
		if(runtime % 100 == 0){
			motorR.setDiff();
			motorL.setDiff();
		}

		logToBatteryC = light.getBrightness();
		logToAdcC[0] = motorR.getCount();
		logToAdcC[1] = motorL.getCount();
		
		switch(phase){
			case 0:
				if(jumper.run()){
					phase++;
				}
				break;
			case 1:
				driver.drive(0, 0);
				break;
		}
		lcd.clear(); // clear data buffer at row 1
		if (btConnected){		
			hoseimX = command.mX - offsetmX;
			hoseimY = command.mY - offsetmY;
			
			daq.send(logToDataC, logToBatteryC, logToAdcC, logToMotorrevC);
			
			lcd.clear(); // clear data buffer at row 1
			lcd.putf("dd", hoseimX,0, hoseimY, 5);
		}else{
			int flag = 0;
			// if(colorDetector.blackLineDetect()){
			// 	flag = 1;
			// }else{
			// 	flag = 0;
			// }
			lcd.putf("ddd", oHolder.getBlack(), 0, oHolder.getWhite(), 4, flag, 7);
		}
		lcd.disp();
		clk.wait(4); /* 10msec wait */

		runtime += 4;
	}

}
