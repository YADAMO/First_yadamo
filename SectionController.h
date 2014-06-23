#pragma once
#include "GrayDetector.h"
#include "PositionEstimater.h"
#include "LineTracer.h"

enum Sections {FIRST_SECTION, SCOND_SECTION, };

class SectionController
{
public:
	SectionController();
	~SectionController();
	void changeSection(int setting_position);
	int getCurPosition();
private:
	int cur;
};
