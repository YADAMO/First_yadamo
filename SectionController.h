#pragma once
#include "GrayDetector.h"
#include "PositionEstimater.h"
#include "LineTracer.h"
#include "Pid.h"

namespace std {}
using namespace std;

enum eSection{E_LineTrace = 0, E_Sumo = 1};

class SectionController
{
public:
	SectionController();
	~SectionController();
	void changeSection(int setting_position);
	int getCurSection();
private:
	int current_section;
};