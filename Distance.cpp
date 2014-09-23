#include "Distance.h"

Distance::Distance(Motor *rm, Motor *lm){
	motorR = rm;
	motorL = lm;
	rightOffset = 0;
	leftOffset = 0;
}

// Distance::Distance(S32 L, S32 R){
// 	rightOffset = R;
// 	leftOffset = L;
// }

Distance::~Distance(){

}

void Distance::init(void){
	leftOffset = motorL->getCount();
	rightOffset = motorR->getCount();
}

F32 Distance::getDistance(void){
	static const F32 DPOD = 0.06981317F;
	
	distanceL = motorL->getCount() - leftOffset;
	distanceR = motorR->getCount() - rightOffset;
	
	distance = F32(distanceL + distanceR) / 2.0;
	distance = distance * DPOD;
	
	return distance;
}
