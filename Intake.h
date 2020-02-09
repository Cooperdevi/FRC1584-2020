/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "OurDefines.h"
class Intake {
 public:
  Intake();
  void SpinUpMax();
  void SpinUpPartial(double speed);
  void Unjam();
  void Stop();
  private: 
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMain;//, /*IntakeFollow,*/ Conveyor;
    void SetIntakeSpeed(double speed) {
      IntakeMain.Set(speed);
    }
};
