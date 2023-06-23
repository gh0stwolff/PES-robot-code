#include "mbed.h"
#include "Motor.h"
#include "IRSensor.h"
#include "TimeMode.h"
#include <cstdio>
#include <utility>

TimeMode mode(D11, D12, D13, D14);
InterruptIn button(D10);

Timer RunTime;

MotorController Motors(D3, D5, D6, D9, 0.2f);
IRSensor links(A2);
IRSensor vooruit(A1);
IRSensor rechts(A0);

DigitalIn Forward(D2);
DigitalIn Backward(D4);
DigitalIn Turn(D8);

enum DriveState {Vooruit, Achteruit, Linksom, Rechtsom, Stop};
DriveState DState = Stop;

#define AVOIDDISTANCE 15.f

#define STEPTIME 500ms

void CheckSensors() {
    float ForwardDistance = vooruit.GetDistance();
    float RightDistance = rechts.GetDistance();
    float LeftDistance = links.GetDistance();

    bool avoidForward = ForwardDistance < AVOIDDISTANCE && ForwardDistance > 0.f;
    bool avoidRight = RightDistance < AVOIDDISTANCE && RightDistance > 0.f;
    bool avoidLeft = LeftDistance < AVOIDDISTANCE && LeftDistance > 0.f;


    if (avoidForward) {
        if (avoidRight) {
            DState = Linksom;
        }
        else if (avoidLeft) {
            DState = Rechtsom;
        }
        else {
            DState = Rechtsom;
        }
    }
    else if (avoidRight) {
        DState = Linksom;
    }
    else if (avoidLeft) {
        DState = Rechtsom;
    }
    else {
        DState = Vooruit;
    }
}

void changeMode(void) {
    if (RunTime.read_ms() > 200) {
        mode.StepMode();
        RunTime.reset();
    }
}


// main() runs in its own thread in the OS
int main()
{
    Forward.mode(PullDown);
    Backward.mode(PullDown);
    Turn.mode(PullDown);

    RunTime.start();

    button.rise(&changeMode);


    while(true) {

        //kijk naar de tijd en stop wanneer het er voorbij is
        if (RunTime.read_ms() < mode.GetTimeModeMS()) 
        {

            CheckSensors();

            switch (DState) {
                case Vooruit:
                    Motors.Drive(1.f);
                    break;
                case Achteruit:
                    Motors.Drive(-1.f);
                    break;
                case Linksom:
                    Motors.TurnLeft(1.f);
                    break;
                case Rechtsom:
                    Motors.TurnRight(1.f);
                    break;
                case Stop:
                    Motors.Stop();
                    break;
            }

            Motors.Update();

            ThisThread::sleep_for(STEPTIME);

        }
        if (RunTime.read_ms() > 5000) {
            mode.lightOff();
        }
    }
}

