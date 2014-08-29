#include "OffsetHolder.h"

OffsetHolder::OffsetHolder(){
}

OffsetHolder::~OffsetHolder(){
}

void OffsetHolder::setBlack(S16 value){
	black = value;
}

S16 OffsetHolder::getBlack(){
	return black;
}

void OffsetHolder::setWhite(S16 value){
	white = value;
}

S16 OffsetHolder::getWhite(){
	return white;
}
