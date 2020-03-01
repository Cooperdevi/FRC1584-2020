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
  void ManualDrive(double magnitude, double direction, bool squared);
  void Aim(double error);
  double GetLeftPosition();
  double GetRightPosition();
  double GetLeftVelocity();
  double GetRightVelocity();
  double GetLeftRearVelocity();
  double GetRightRearVelocity();
  void TurnToAngle(double angle);
  double GetAngle();
  void SetAngle();
  void MoveToDistance(double distance);
  void SetDistance(double distance);
  void SetVelocity(double velocity);
  bool IsStopped();
  void TestDrive();
  void MoveToPoint(double point);
void AbsoluteTurn(double rotate)
      {
        double gyroAngle = Gyro.GetAngle();
        angle = (int)(gyroAngle/360.0)*360.0 + rotate;
        if(angle - gyroAngle > 180)
        {
          angle = angle -360;
        }
        else if(angle- gyroAngle < -180)
        {
          angle = angle + 360;
        }
      }
    void AutoDrive(double magnitude, double rotateDrive);
        frc::ADIS16448_IMU Gyro;
        bool GetAiming();
    static double SignOf(double input);

  //void AutoDrive(int position);
  private:
    ctre::phoenix::motorcontrol::can::WPI_TalonFX /*ltTalon,*/ lfTalon,  /*rtTalon,*/ rfTalon, lrTalon, rrTalon;
//  ctre::phoenix::motorcontrol::TalonFXSensorCollection::TalonFXSensorCollection left, right;
    ctre::phoenix::motorcontrol::TalonFXSensorCollection& left, right, leftRear, rightRear;
        double originalAngle;
        double originalLeftPosition;
    bool looping;
    bool preventLooping;
    void AllowLooping();
    void EndLooping();
    double angle;
    bool aiming;
};
