/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveTrain.h"

DriveTrain::DriveTrain() :
    frc::DifferentialDrive(lfTalon, rfTalon),
    /*ltTalon(LT_TALON),*/ lfTalon(LF_TALON), rfTalon(RF_TALON), lrTalon(LR_TALON), /*rtTalon(RT_TALON),*/  rrTalon(RR_TALON), left(lfTalon.GetSensorCollection()), right(rfTalon.GetSensorCollection()), looping(false), preventLooping(false)
{
        lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
   // lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LT_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);
}

void DriveTrain::ManualDrive(double magnitude, double direction) {
    //ArcadeDrive(magnitude, direction, false);  
    EndLooping();
    if(!looping) {
        if(fabs(GetLeftVelocity() + GetRightVelocity()) / 2 < 10000) {
            ArcadeDrive(magnitude, direction, false);
        }
        else {
        CurvatureDrive(magnitude, direction, false);// IsStopped());
        }
    }
    AllowLooping();
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
    EndLooping();
    ArcadeDrive(0, adjust, false);
    AllowLooping();
}

double DriveTrain::GetLeftPosition() {
    return left.GetIntegratedSensorPosition();
}

double DriveTrain::GetRightPosition() {
    return right.GetIntegratedSensorPosition();
}

double DriveTrain::GetLeftVelocity() {
    return left.GetIntegratedSensorVelocity();
}

double DriveTrain::GetRightVelocity() {
    return right.GetIntegratedSensorVelocity();
}

void DriveTrain::TurnToAngle(double angle) {
 //   double originalAngle = GetAngle();
    EndLooping();

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
    AllowLooping();
}

double DriveTrain::GetAngle() {
    return(fmod(Gyro.GetAngle(), 360));
}

void DriveTrain::SetAngle(double angle) {
    originalAngle = angle;
}

void DriveTrain::MoveToDistance(double distance) {
   /* if(fabs(GetLeftPosition() - originalLeftPosition + distance) < DRIVE_DISTANCE_TOLERANCE) {
        if(GetLeftPosition() < distance) {
            ArcadeDrive(fabs(DRIVE_DISTANCE_P * (distance - originalLeftPosition)) < 1 ? DRIVE_DISTANCE_P * (distance - originalLeftPosition) : DRIVE_DISTANCE_P * (distance - originalLeftPosition)/fabs(DRIVE_DISTANCE_P * (distance - originalLeftPosition)), 0, false);
        }
        else {
            ArcadeDrive(fabs(-DRIVE_DISTANCE_P * (distance - originalLeftPosition)) < 1 ? -DRIVE_DISTANCE_P * (distance - originalLeftPosition) : -DRIVE_DISTANCE_P * (distance - originalLeftPosition)/fabs(-DRIVE_DISTANCE_P * (distance - originalLeftPosition)), 0, false);
        }
    }
    else {
        ArcadeDrive(0, 0); 
    }*/
    if(!preventLooping) {
    looping = true;
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Position, distance);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Position, distance);
    }
}

void DriveTrain::SetDistance(double distance) {
    originalLeftPosition = distance;
}

void DriveTrain::SetVelocity(double velocity) {
  //  double velocityDiffLeft = GetLeftVelocity() - velocity;
  /*  double velocityDiffRight = GetRightVelocity() - velocity;
    if(fabs(velocityDiffLeft) > VELOCITY_TOLERANCE || fabs(velocityDiffRight) > VELOCITY_TOLERANCE) {
        if(fabs(velocityDiffLeft) > VELOCITY_TOLERANCE) {
            TankDrive(fabs(VELOCITY_P * velocityDiffLeft) < 1 ? VELOCITY_P * velocityDiffLeft : SignOf(velocityDiffLeft), 0., false);
        }
        if(fabs(velocityDiffRight) > VELOCITY_TOLERANCE) {
            TankDrive(0., fabs(VELOCITY_P * velocityDiffRight) < 1 ? VELOCITY_P * velocityDiffRight : SignOf(velocityDiffRight), false);
        }
    }
    else {
        TankDrive(0., 0., false);
    }*/
    if(!preventLooping) {
    looping = true;
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    //lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    //rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);

    }
    /*if(fabs(GetLeftVelocity() - velocity) > 75) {
        TankDrive(fabs((.005 * (GetLeftVelocity() - velocity)) < 1 ? -(.005 * (GetLeftVelocity() - velocity)) : .005 * (GetLeftVelocity() - velocity)/fabs(.005 * (GetLeftVelocity() - velocity))), 0., false);
    }
    else if(fabs(GetRightVelocity() - velocity) > 75) {
        TankDrive(0., fabs((.005 * (GetRightVelocity() - velocity)) < 1 ? -(.005 * (GetRightVelocity() - velocity)) : .005 * (GetRightVelocity() - velocity) / fabs (.005 * (GetRightVelocity() - velocity))), false);
    }
    else {
        TankDrive(0, 0, false);
    }*/
}

double DriveTrain::SignOf(double input) {
    return input/fabs(input);
}

void DriveTrain::EndLooping() {
    preventLooping = true;
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
 //   lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);

  //  rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);  
    looping = false;
}

void DriveTrain::AllowLooping() {
    preventLooping = false;
}


bool DriveTrain::IsStopped() {
    if(GetLeftVelocity() < VELOCITY_TOLERANCE && GetRightVelocity() < VELOCITY_TOLERANCE) {
        return true;
    }
    return false;
}
