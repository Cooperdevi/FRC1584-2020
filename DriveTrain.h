/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "frc/drive/DifferentialDrive.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonFX.h"
//#include <TalonFXSensorCollection.h>
#include "adi/ADIS16448_IMU.h"
#include "ctre/Phoenix.h"
#include "OurDefines.h"

class DriveTrain : public frc::DifferentialDrive {
 public:
  DriveTrain();
  void ManualDrive(double magnitude, double direction);
  void Aim(double error);
  double GetLeftPosition();
  double GetRightPosition();
  double GetLeftVelocity();
  double GetRightVelocity();
  void TurnToAngle(double angle);
  double GetAngle();
  void SetAngle(double angle);
  void MoveToDistance(double distance);
  void SetDistance(double distance);
  void SetVelocity(double velocity);
  bool IsStopped();

  //void AutoDrive(int position);
  private:
    ctre::phoenix::motorcontrol::can::WPI_TalonFX /*ltTalon,*/ lfTalon,  /*rtTalon,*/ rfTalon, lrTalon, rrTalon;
//  ctre::phoenix::motorcontrol::TalonFXSensorCollection::TalonFXSensorCollection left, right;
    ctre::phoenix::motorcontrol::TalonFXSensorCollection& left, right;
        frc::ADIS16448_IMU Gyro;
        double originalAngle;
        double originalLeftPosition;
    double SignOf(double input);
    bool looping;
    bool preventLooping;
    void AllowLooping();
    void EndLooping();
   
};
