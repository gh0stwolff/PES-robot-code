#ifndef MBED_IRSENSOR
#define MBED_IRSENSOR

#include "mbed.h"

class IRSensor {
private:
    AnalogIn sensor;
public:
    IRSensor(PinName);
    float GetDistance();

};

#endif