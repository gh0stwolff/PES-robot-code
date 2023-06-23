#ifndef MBED_TIMEMODE_H
#define MBED_TIMEMODE_H

#include "mbed.h"

class TimeMode {
private:
    DigitalOut led1;
    DigitalOut led2;
    DigitalOut led3;
    DigitalOut led4;

    float setTime = 0.f;

    enum looptijd {kwartier, halfuur, uur, tweeUur};
    looptijd mode = kwartier;

public:

    TimeMode(PinName, PinName, PinName, PinName);

    void StepMode();
    float GetTimeModeMS();
    void lightOff();

private:
    void updateLed();
};


#endif