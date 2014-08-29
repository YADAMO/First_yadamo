#pragma once
#include "ColorDetector.h"
#include "PositionEstimater.h"
#include "LineTracer.h"

namespace std {}
using namespace std;

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
