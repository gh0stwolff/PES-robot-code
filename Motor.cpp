#include "Motor.h"


MotorController::MotorController
(PinName Motor1Forward, PinName Motor1Backward, PinName Motor2Forward, PinName Motor2Backward, float StepSpeed) : 
LeftMotorForward(Motor1Forward), LeftMotorBackward(Motor1Backward),
 RightMotorForward(Motor2Forward), RightMotorBackward(Motor2Backward), STEPSPEED(StepSpeed)
{ }

void MotorController::Update() {

    switch (state) {
        case drive:
            
            if (desiredSpeed > 0 ) {
                driveForward(desiredSpeed);
            }
            else {
                driveBackward(desiredSpeed * -1);
            }
            break;
        case turnLeft:
            turnleft(desiredSpeed);
            break;
        case turnRight:
            turnright(desiredSpeed);
            break;
        case stop:
            brake();
            break;
        case idle: {

            break;
        }
    }
}

void MotorController::Drive(float speed) {
    desiredSpeed = speed;
    state = drive;
}

void MotorController::driveForward(float speed) {
    if (Motor1ForwardSpeed < speed && Motor2ForwardSpeed >= Motor1ForwardSpeed) {
        Motor1ForwardSpeed += STEPSPEED;
    }

    if (Motor2ForwardSpeed < speed && Motor1ForwardSpeed >= Motor2ForwardSpeed) {
        Motor2ForwardSpeed += STEPSPEED;
    }

    if (Motor1ForwardSpeed >= speed) {
        Motor1ForwardSpeed = speed;
    }

    if (Motor2ForwardSpeed >= speed) {
        Motor2ForwardSpeed = speed;
    }

    if (Motor1BackwardSpeed > 0 || Motor2BackwardSpeed > 0) {
        brakeBackward();
    }

    LeftMotorForward.write(Motor1ForwardSpeed);
    RightMotorForward.write(Motor2ForwardSpeed);

}

void MotorController::driveBackward(float speed) {
    if (Motor1BackwardSpeed < speed && Motor2BackwardSpeed >= Motor1BackwardSpeed) {
        Motor1BackwardSpeed += STEPSPEED;
    }

    if (Motor2BackwardSpeed < speed && Motor1BackwardSpeed >= Motor2BackwardSpeed) {
        Motor2BackwardSpeed += STEPSPEED;
    }

    if (Motor1BackwardSpeed >= speed) {
        Motor1BackwardSpeed = speed;
    }

    if (Motor2BackwardSpeed >= speed) {
        Motor2BackwardSpeed = speed;
    }

    if (Motor1ForwardSpeed > 0 || Motor2ForwardSpeed > 0) {
        brakeForward();
    }

    LeftMotorBackward.write(Motor1BackwardSpeed);
    RightMotorBackward.write(Motor2BackwardSpeed);
}

void MotorController::TurnLeft(float speed) {
    state = turnLeft;
    desiredSpeed = speed;
}

void MotorController::turnleft(float speed) {
    if (Motor1BackwardSpeed < speed && Motor2ForwardSpeed >= Motor1BackwardSpeed) {
        Motor1BackwardSpeed += STEPSPEED;
    }

    if (Motor1BackwardSpeed >= speed) {
        Motor1BackwardSpeed = speed;
    }

    if (Motor2ForwardSpeed < speed && Motor1BackwardSpeed >= Motor2ForwardSpeed) {
        Motor2ForwardSpeed += speed;
    }

    if (Motor2ForwardSpeed >= speed) {
        Motor2ForwardSpeed = speed;
    }

    LeftMotorForward.write(0);
    LeftMotorBackward.write(Motor1BackwardSpeed);

    RightMotorForward.write(Motor2ForwardSpeed);
    RightMotorBackward.write(0);
}

void MotorController::TurnRight(float speed) {
    state = turnRight;
    desiredSpeed = speed;
}

void MotorController::turnright(float speed) {
    if (Motor1ForwardSpeed < speed && Motor2BackwardSpeed >= Motor1ForwardSpeed) {
        Motor1ForwardSpeed += STEPSPEED;
    }

    if (Motor1ForwardSpeed >= speed) {
        Motor1ForwardSpeed = speed;
    }

    if (Motor2BackwardSpeed < speed && Motor1ForwardSpeed >= Motor2BackwardSpeed) {
        Motor2BackwardSpeed += STEPSPEED;
    }

    if (Motor2BackwardSpeed >= speed) {
        Motor2BackwardSpeed = speed;
    }

    LeftMotorForward.write(Motor1ForwardSpeed);
    LeftMotorBackward.write(0);

    RightMotorForward.write(0);
    RightMotorBackward.write(Motor2BackwardSpeed);
}

void MotorController::Stop() {
    state = stop;
}

void MotorController::brake() {
    brakeForward();
    brakeBackward();
}

void MotorController::brakeBackward() {
    if (Motor1BackwardSpeed > 0) {
        Motor1BackwardSpeed -= STEPSPEED;
    }

    if (Motor2BackwardSpeed > 0) {
        Motor2BackwardSpeed -= STEPSPEED;
    }

    if (Motor1BackwardSpeed <= 0) {
        Motor1BackwardSpeed = 0.f;
    }

    if (Motor2BackwardSpeed <= 0) {
        Motor2BackwardSpeed = 0.f;
    }

    LeftMotorBackward.write(Motor1BackwardSpeed);
    RightMotorBackward.write(Motor2BackwardSpeed);
}

void MotorController::brakeForward() {
    if (Motor1ForwardSpeed > 0) {
        Motor1ForwardSpeed -= STEPSPEED;
    }

    if (Motor2ForwardSpeed > 0) {
        Motor2ForwardSpeed -= STEPSPEED;
    }

    if (Motor1ForwardSpeed <= 0) {
        Motor1ForwardSpeed = 0.f;
    }

    if (Motor2ForwardSpeed <= 0) {
        Motor2ForwardSpeed = 0.f;
    }

    LeftMotorForward.write(Motor1ForwardSpeed);
    RightMotorForward.write(Motor2ForwardSpeed);
}