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
#include "frc/DigitalInput.h"
#include "frc/Servo.h"
#include "frc/Timer.h"
#include <iostream>
#include <chrono>
#include <thread>


class Intake {
 public:
  Intake();
  void Initialize();
  void SpinUpMax();
  void SpinUpPartial(double speed);
  void Unjam();
  void Stop();
  void Toggle(double desired);
  void TalonTest(double test);
  int Capacity();
  void Run();
  bool JustPressedSwitchEntry();
  bool JustPressedSwitchExit();
  void SwitchState();
  void SwitchState(bool targetState);
  bool GetState();
  void TakeIn();
  void Feed();
  private: 
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMain, Conveyor, Lift, Lock;
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX Test;
    //, /*IntakeFollow,*/ Conveyor;
    void SetIntakeSpeed(double speed) {
      IntakeMain.Set(speed);
    }
    int capacity;
    frc::DigitalInput Entry, Exit;
    bool firstTime;
    frc::Servo Compressor;
    bool state; //false for intake, true for feeding
    bool gotBall;
  frc::Timer IntakeTimer;
};
