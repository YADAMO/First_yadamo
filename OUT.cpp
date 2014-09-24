#include "OUT.h"

OUT::OUT(Basic *bs, Jumper *jp, GridRunner *gr, ParkingP *pP){
	basic = bs;
	jumper = jp;
	gridRunner = gr;
	parkingP = pP;
	phase = 0;
}

OUT::~OUT(){

}

bool OUT::run(){
	switch(phase){
		case 0:
			if(basic->runOUT()){
				phase++;
			}
			break;
		case 1:
			if(jumper->run()){
				phase++;
			}
			break;
		case 2:
			if(basic->runToGrid()){
				phase = 10;
			}
			break;
		case 3:
			if(gridRunner->run()){
				phase++;
			}
			break;
		case 4:
			break;
		case 10:
			return true;
			break;
	}
	return false;
}
