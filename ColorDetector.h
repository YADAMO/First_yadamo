#pragma once

class ColorDetector{
private:
	ColorDetector();
    int threshold;
    int buffer[10];
public:
    bool grayDetect();
};

