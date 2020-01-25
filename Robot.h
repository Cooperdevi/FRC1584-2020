/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "DriveTrain.h"
#include "DriverInput.h"
#include "OurDefines.h"
#include "Launcher.h"
#include "Intake.h"
#include "VisionProcessing.h"
/*
typedef enum{AUTO_ANGLE, AUTO_DRIVE, AUTO_AIM, AUTO_SHOOT, AUTO_STOP} command_t;
typedef struct {
	command_t command;
	long distance;
	float heading;
} wayPoint_t; */
class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  void RunDrive();
  void RunShooter();
  void RunAim();
  void RunIntake();
  void Disconnects();
//  bool DriveDisable, ShooterDisable, AimDisable, ClimbDisable, IntakeDisable;
  DriveTrain Drive;
  DriverInput DriverController;
  Launcher Shooter;
  Intake Entry;
  VisionProcessing Targeting;
  int position;
  wayPoint_t* wayPointSet;
  wayPoint_t* WP[5] =	{WP0, WP1, WP2, WP3, WP4};
  wayPoint_t WP0[6] = { 
    {AUTO_ANGLE, 0, 30},
    {AUTO_DRIVE, 40000, 0},
    {AUTO_ANGLE, 0, -30},
    {AUTO_AIM, 0, 0},
    {AUTO_SHOOT, 0, 0},
    {AUTO_STOP, 0, 0}
  };
  wayPoint_t WP1[4] = {
    {AUTO_DRIVE, 40000, 0},
    {AUTO_AIM, 0, 0},
    {AUTO_SHOOT, 0, 0},
    {AUTO_STOP, 0, 0}
  };
  wayPoint_t WP2[5] = {
    {AUTO_DRIVE, 40000, 0},
    {AUTO_ANGLE, 0, 30},
    {AUTO_AIM, 0, 0},
    {AUTO_SHOOT, 0, 0},
    {AUTO_STOP, 0, 0}
  };
  wayPoint_t WP3[6] = { 
    {AUTO_ANGLE, 0, -30},
    {AUTO_DRIVE, 40000, 0},
    {AUTO_ANGLE, 0, 30},
    {AUTO_AIM, 0, 0},
    {AUTO_SHOOT, 0, 0},
    {AUTO_STOP, 0, 0}
  };
  wayPoint_t WP4[2] = {
    {AUTO_DRIVE, 40000, 0},
    {AUTO_STOP, 0, 0}
  };


};
