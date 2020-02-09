/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "OurDefines.h"
class Climber {
 public:
  Climber();
  void Release();
  void Retract();
  
 private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX ClimberMotor;

};
