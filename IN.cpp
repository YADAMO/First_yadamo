#include "IN.h"

IN::IN(Basic *bs, Mogul *mg, Figure *fg){
	basic = bs;
	mogul = mg;
	figure = fg;
	phase = 1;
}

IN::~IN(){

}

bool IN::run(){
	switch(phase){
		case 0:
			if(basic->runIN()){
				phase++;
			}
			break;
		case 1:
			if(mogul->run()){
				phase++;
			}
			break;
		case 2:
			if(basic->runToFigure()){
				phase++;
			}
			break;
		case 3:
			if(figure->run()){
				phase++;
			}
			break;
		case 4:
			return true;
			break;
	}
	return false;
}
