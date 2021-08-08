// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SFDrive.h"
#include <math.h>

SFDrive::SFDrive(rev::CANSparkMax* lMotor, rev::CANSparkMax* rMotor) : lMotor{lMotor}, rMotor{rMotor} {}

double excessHandler(double value)
{
    if (value > 1.0)
        value = -(value - 1.0);
    else if (value < -1.0)
        value = -(value + 1.0);
    else
        value = 0.0;
    return value;
}

void SFDrive::ArcadeDrive(double xSpeed, double zRotation) 
{
    double leftMotorOutput, rightMotorOutput;

    if (abs(xSpeed) < deadband)
        xSpeed = 0;

    if (abs(zRotation) < deadband)
        zRotation = 0;

    if (xSpeed >= 0.0) {
        leftMotorOutput = xSpeed + zRotation;
        rightMotorOutput = xSpeed - zRotation;
    }
    else {
        leftMotorOutput = xSpeed - zRotation;
        rightMotorOutput = xSpeed + zRotation;
    }

    leftMotorOutput = leftMotorOutput + excessHandler(rightMotorOutput);
    rightMotorOutput = rightMotorOutput + excessHandler(leftMotorOutput);

    leftMotorOutput = std::copysign(pow(leftMotorOutput, 2), leftMotorOutput);
    rightMotorOutput = std::copysign(pow(rightMotorOutput, 2), rightMotorOutput);

    lMotor->Set(leftMotorOutput);
    rMotor->Set(rightMotorOutput);
}