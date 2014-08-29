#pragma once
#include "GrayDetector.h"
#include "PositionEstimater.h"

namespace std {}
using namespace std;

enum eSection{E_LineTrace = 0, E_Sumo = 1};

class SectionController
{
public:
	SectionController();
	~SectionController();
	void changeSection(int next_section);
	int getCurSection();
private:
	int current_section;
};
