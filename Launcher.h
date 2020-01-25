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
#include "frc/Timer.h"

class Launcher {
 public:
  Launcher();
  void Shoot();
  void SpinUpMax();
  void SpinUpPartial(double speed);
  void StopSpin();
  void Aim(double distance);
  void ShootFullAuto();
  void StopShooting();
  int Capacity();
private:
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX ShooterMain, ShooterFollow;
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX Trigger;
  frc::Timer TriggerTimer;
  void SetSpin(double speed);
};
