#include "TimeMode.h"

TimeMode::TimeMode(PinName Led1, PinName Led2, PinName Led3, PinName Led4) :
    led1(Led1), led2(Led2), led3(Led3), led4(Led4)
{
}

void TimeMode::StepMode() {
    switch(mode) {
        case kwartier:
            mode = halfuur;
            setTime = 30 * 60 * 1000;
            break;
        case halfuur:
            mode = uur;
            setTime = 60 * 60 * 1000;
            break;
        case uur:
            mode = tweeUur;
            setTime = 120 * 60 * 1000;
            break;
        case tweeUur:
            mode = kwartier;
            setTime = 15 * 60 * 1000;
    }

    updateLed();
}

float TimeMode::GetTimeModeMS() {
    return setTime;
}

void TimeMode::lightOff() {
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
}

void TimeMode::updateLed() {
    switch (mode) {
        case kwartier:
            led1 = 1;
            led2 = 0;
            led3 = 0;
            led4 = 0;
            break;
        case halfuur:
            led1 = 0;
            led2 = 1;
            led3 = 0;
            led4 = 0;
            break;
        case uur:
            led1 = 0;
            led2 = 0;
            led3 = 1;
            led4 = 0;
            break;
        case tweeUur:
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 1;
            break;
    }
}