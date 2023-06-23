#ifndef MBED_MOTORCONTROLLER_H
#define MBED_MOTORCONTROLLER_H

#include "mbed.h"

class MotorController {
private:
    PwmOut LeftMotorForward;
    PwmOut LeftMotorBackward;

    PwmOut RightMotorForward;
    PwmOut RightMotorBackward;

    float Motor1ForwardSpeed = 0.f;
    float Motor1BackwardSpeed = 0.f;
    float Motor2ForwardSpeed = 0.f;
    float Motor2BackwardSpeed = 0.f;

    float desiredSpeed = 0.f;

    enum State {drive, turnLeft, turnRight, stop, idle};
    State state = State::idle;

    float STEPSPEED;

public:
    MotorController(PinName, PinName, PinName, PinName, float);
    void Update();

    void Drive(float);
    void TurnLeft(float);
    void TurnRight(float);
    void Stop();

private:
    void driveForward(float);
    void driveBackward(float);
    void turnleft(float);
    void turnright(float);

    void brake();
    void brakeBackward();
    void brakeForward();


};

#endif