#include "Distance.h"

Distance::Distance(){
	rightOffset = 0;
	leftOffset = 0;
}

Distance::Distance(S32 L, S32 R){
	rightOffset = R;
	leftOffset = L;
}

Distance::~Distance(){

}

void Distance::init(S32 L, S32 R){
	leftOffset = L;
	rightOffset = R;
}

F32 Distance::getDistance(S32 L, S32 R){
	static const F32 DPOD = 0.06981317F;
	
	distanceL = L - leftOffset;
	distanceR = R - rightOffset;
	
	distance = F32(distanceL + distanceR) / 2.0;
	distance = distance * DPOD;
	
	return distance;
}
