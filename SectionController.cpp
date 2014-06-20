#include "SectionController.h"

SectionController::SectionController()
{
	cur = FIRST_SECTION;
}

SectionController::~SectionController()
{
}

void SectionController::changeSection(int setting_position)
{
	cur = setting_position;
}

//必要であると感じました
int SectionController::getCurPosition()
{
	return cur;
}
