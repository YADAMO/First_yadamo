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
#include "GridRunner.h"
#include "Basic.h"
#include "ParkingL.h"
#include "ParkingP.h"
#include "IN.h"
#include "OUT.h"

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
#define GYRO	PORT_1

Bluetooth bt;
static const CHAR* PASSKEY = "YADAMO";

TouchSensor touch(TOUCH);
Nxt nxt;
Clock clk;

OffsetHolder oHolder;
SectionController sectionController;
Speaker speaker;
GyroSensor gyroSensor(GYRO);
Motor motorL(DRIVE_L,true);
Motor motorR(DRIVE_R,true);
Motor motorS(STEER,true);
Driver driver(&motorL, &motorR, &motorS);
Distance distance(&motorR, &motorL);
LightSensor light(LIGHT);
Pid pid(&light);
LineTracer lineTracer(&driver, &pid, &oHolder);
TouchJudgement touchJudgement(&touch);
ColorDetector colorDetector(&light, &oHolder);
UI ui(&light, &touchJudgement, &lineTracer, &clk, &speaker, &oHolder);
ReturnLine returnLine(&driver, &light, &colorDetector);
StepDetector stepDetector(&motorR, &motorL, &speaker);
Stepper stepper(&stepDetector, &lineTracer, &driver, &pid, &distance);
Figure figure(&lineTracer, &colorDetector, &driver, &stepper, &oHolder, &distance);
Mogul mogul(&driver, &lineTracer, &stepDetector, &stepper, &distance, &pid);
Jumper jumper(&driver, &lineTracer, &stepper, &distance, &stepDetector);
GridRunner gridRunner(&lineTracer, &driver, &stepper, &colorDetector, &distance, &stepDetector);
Basic basic(&lineTracer, &pid, &speaker, &distance, &motorR, &motorL, &oHolder);
ParkingL parkingL(&lineTracer, &driver, &stepDetector, &distance);
ParkingP parkingP(&lineTracer, &driver, &colorDetector, &distance);
IN in(&basic, &mogul, &figure, &parkingL);
OUT out(&basic, &jumper, &gridRunner, &parkingP);


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
	
	int offsetmX = 0;
	int offsetmY = 0;
	
	if (btConnected){
		command = gp.get();
		lcd.clear();
		lcd.putf("s", (gp.isConnected() ? "connected": "not connected"));
		offsetmX = command.mX;
		offsetmY = command.mY;
	}
	
	int hoseimX;
	int hoseimY;
	
	S8 logToDataC[2];
	logToDataC[0] = 1;//data1
	logToDataC[1] = 2;//data2
	U16 logToBatteryC = 3;//data3
	S16 logToAdcC[4];
	logToAdcC[0] = 4;//data7
	logToAdcC[1] = 5;//data8
	logToAdcC[2] = 6;//data9
	logToAdcC[3] = 7;

	S32 logToMotorrevC[4];
	logToMotorrevC[0] = 8;//data4
	logToMotorrevC[1] = 9;//data5
	logToMotorrevC[2] = 10;//data6
	logToMotorrevC[3] = 11;	
	
	int runtime = 0;
	int phase = 0;
	while(1)
	{
		
//		driver.operate(hoseimX, hoseimY);
		// if(runtime % 20 == 0){
			motorR.setDiff();
			motorL.setDiff();
		// }

		logToBatteryC = light.getBrightness();
		logToMotorrevC[0] = (S32)distance.getDistance();
		logToMotorrevC[1] = motorL.getCount();
		logToMotorrevC[2] = motorR.getCount();

		logToAdcC[0] = gyroSensor.getAnglerVelocity();
		
		switch(phase)
		{
			case 0:
				// driver.straight(30);

				// pid.changePid(0.27, 0.001, 0.023);
				// lineTracer.lineTrace(20, 1);
				// if(runtime > 400){
				// 	phase++;
				// }
				// basic.runIN();
				// mogul.run();
				// if(parkingP.run()){
				// if(parkingL.run()){
				// if(out.run()){
				// if(basic.runToGrid()){
				if(gridRunner.run()){
					phase++;
					driver.straightInit();
				}
				break;
			case 1:
				driver.straight(0);
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
			lcd.putf("ddd", (int)distance.getDistance(), 0, oHolder.getWhite(), 4, flag, 7);
		}
		lcd.disp();
		clk.wait(4); /* 10msec wait */

		runtime += 4;
	}

}
