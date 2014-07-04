#pragma once

class GrayDetector{
private:
	GrayDetector();
    int threshold;
    int buffer[10];
public:
    bool grayDetect();
};

