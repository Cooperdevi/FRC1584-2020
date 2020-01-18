/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveTrain.h"

DriveTrain::DriveTrain() :
    frc::RobotDrive(lfTalon, rfTalon),
    /*ltTalon(LT_TALON),*/ lfTalon(LF_TALON), lrTalon(LR_TALON), /*rtTalon(RT_TALON),*/ rfTalon(RF_TALON), rrTalon(RR_TALON)
{
   // lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LT_TALON);
    lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);
}

void DriveTrain::ManualDrive(double magnitude, double direction) {
    ArcadeDrive(magnitude, direction, false);  
}
