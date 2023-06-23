#include "IRSensor.h"


IRSensor::IRSensor(PinName pin) : sensor(pin) {

}

float IRSensor::GetDistance() {
    float spanning = sensor.read() * 3.f;

    // y = 18,586 X + 0,0503
    return 1/(spanning/18.586 - (0.0503/18.586));
}

