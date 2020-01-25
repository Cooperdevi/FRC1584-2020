/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveTrain.h"

DriveTrain::DriveTrain() :
    frc::DifferentialDrive(lfTalon, rfTalon),
    /*ltTalon(LT_TALON),*/ lfTalon(LF_TALON), lrTalon(LR_TALON), /*rtTalon(RT_TALON),*/ rfTalon(RF_TALON), rrTalon(RR_TALON), left(lfTalon.GetSensorCollection()), right(rfTalon.GetSensorCollection())
{
   // lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LT_TALON);
    lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);
}

void DriveTrain::ManualDrive(double magnitude, double direction) {
    ArcadeDrive(magnitude, direction, false);  
}
/*
void DriveTrain::Adjust(double distance, double angle) {
    //double trueDistance = distance <= MAX_ADJUST_DISTANCE ? distance : MAX_ADJUST_DISTANCE;
    double trueAngle = angle <= MAX_ADJUST_ANGLE ? angle : MAX_ADJUST_ANGLE;
    ArcadeDrive(0, trueAngle);
}*/
void DriveTrain::Aim(double error) {
    double adjust = 0;
    double integral = 0;
    double lastError = 0;
    double derivative = 0;
    if(integral < -INTEGRAL_SATURATION || integral > INTEGRAL_SATURATION) {
        integral = INTEGRAL_SATURATION * (integral/fabs(integral));
    }
    if(error > ANGLE_TOLERANCE) {
        integral += error;
        derivative = error - lastError;
        adjust = P * error + I * integral + D * derivative;//+ MINIMUM_FORCE;
        lastError = error;
    }

    ArcadeDrive(0, adjust, false);
}

double DriveTrain::GetLeftPosition() {
    return left.GetIntegratedSensorPosition();
}

double DriveTrain::GetRightPosition() {
    return right.GetIntegratedSensorPosition();
}

void DriveTrain::TurnToAngle(double angle) {
 //   double originalAngle = GetAngle();

    if(fabs((GetAngle() - originalAngle + angle) > DRIVE_ANGLE_TOLERANCE)) { 
        if(angle > 0) { 
            ArcadeDrive(0, DRIVE_ANGLE_P * (angle-originalAngle)/360);
        }
        else {
            ArcadeDrive(0, DRIVE_ANGLE_P * (angle-originalAngle)/360);
        }
    }
    else {
        ArcadeDrive(0, 0);
    }
}

double DriveTrain::GetAngle() {
    return(fmod(Gyro.GetAngle(), 360));
}

void DriveTrain::SetAngle(double angle) {
    originalAngle = angle;
}

void DriveTrain::MoveToDistance(double distance) {
    if(fabs(GetLeftPosition() - originalLeftPosition + distance) < DRIVE_DISTANCE_TOLERANCE) {
        if(GetLeftPosition() < distance) {
            ArcadeDrive(DRIVE_DISTANCE_P * (distance - originalLeftPosition), 0);
        }
        else {
            ArcadeDrive(-DRIVE_DISTANCE_P * (distance - originalLeftPosition), 0);
        }
    }
    else {
        ArcadeDrive(0, 0); 
    }
}

void DriveTrain::SetDistance(double distance) {
    originalLeftPosition = distance;
}