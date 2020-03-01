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
#include "frc/shuffleboard/Shuffleboard.h"
#include "DriveTrain.h"
#include "DriverInput.h"
#include "OurDefines.h"
#include "Launcher.h"
#include "Intake.h"
#include "VisionProcessing.h"
#include "Climber.h"
#include "frc/PowerDistributionPanel.h"

typedef enum{AUTO_ANGLE, AUTO_DRIVE, AUTO_AIM, AUTO_SHOOT, AUTO_STOP} command_t;
typedef struct {
	command_t command;
	long distance;
	float heading;
} wayPoint_t; 
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
 frc::SendableChooser<int> m_positionChooser;

  std::string m_autoSelected;
  frc::PowerDistributionPanel pdp;
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
  Climber Climb;
  int position;
  wayPoint_t* wayPointSet;
  wayPoint_t* WP[5] =	{WP0, WP1, WP2, WP3, WP4};
  wayPoint_t WP0[6] = { //right to left from driver's view; last is default (just move)
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
    {AUTO_DRIVE, 10000, 0},
    {AUTO_STOP, 0, 0}
  };
  double originalDistance;
  bool firstAngle, firstDrive;
  double sensitivity[10] = {.1, .15, .2, .25, .3, .4, .5, .7, .85, 1};
  double shootSpeed[20] = {.05, .1, .15, .2, .25, .3, .35, .4, .45, .5, .55, .6, .65, .7, .75, .8, .85, .9, .95, 1};
  double intakeSpeed[20] = {.05, .1, .15, .2, .25, .3, .35, .4, .45, .5, .55, .6, .65, .7, .75, .8, .85, .9, .95, 1};
  //int sensBool[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//  int shootBool[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//  int intakeBool[20] =  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double currentSens, currentShoot, currentIntake;
  int sensI;// = 9;
  int shootI;// = 9;
  int intakeI;// = 9;
  void RunArrays();
  void RunClimb();
  bool climbUnlock;
  bool firstIntake;
  std::string Status();
  double DistanceConvert(double input);
//  bool first = true;
  bool aiming;
  bool lowSens, highSens, autoAngling, firstAngling, crawling;


};
