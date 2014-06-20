#pragma once
//include header file of gray detector class
//include header file of ecorrent position estimate
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
