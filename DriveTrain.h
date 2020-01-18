/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/RobotDrive.h>
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonFX.h"
#include "adi/ADIS16448_IMU.h"
#include "ctre/Phoenix.h"
#include "OurDefines.h"

class DriveTrain : public frc::RobotDrive {
 public:
  DriveTrain();
  void ManualDrive(double magnitude, double direction);
  private:
    ctre::phoenix::motorcontrol::can::WPI_TalonFX /*ltTalon,*/ lfTalon, lrTalon, /*rtTalon,*/ rfTalon, rrTalon;

};
