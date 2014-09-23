#pragma once
#include "Basic.h"
#include "Mogul.h"
#include "Figure.h"


class IN{
private:
    Basic *basic;
    Mogul *mogul;
    Figure *figure;
    int phase;
public:
	IN(Basic *bs, Mogul *mg, Figure *fg);
    ~IN();
    bool run();
};
