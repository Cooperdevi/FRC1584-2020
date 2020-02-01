/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                   
TODO:
Field oriented control
Feedback loop for shooter   
Configure radio                         */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

/*
typedef enum{AUTO_ANGLE, AUTO_DRIVE, AUTO_AIM, AUTO_SHOOT, AUTO_STOP} command_t;
typedef struct {
	command_t command;
	long distance;
	float heading;
} wayPoint_t; */
Robot::Robot() :
DriverController(0), position(0), wayPointSet(WP4), firstAngle(true), firstDrive(true)
//, DriveDisable(false), ShooterDisable(false), AimDisable(false), ClimbDisable(false), IntakeDisable(false)
{
}

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  Targeting.Initialize();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  Shooter.SetFollower();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartD`ashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
 //// m_autoSelected = m_chooser.GetSelected();
 ///  m_autoSelected = SmartDashboard::GetString("Auto Selector",
 //      kAutoNameDefault);
 // std::cout << "Auto selected: " << m_autoSelected << std::endl;
  position = (int) frc::SmartDashboard::GetNumber("Auto Select", 6);
		frc::SmartDashboard::PutNumber("Auto Select", position);

  //if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
 // } else {
    // Default Auto goes here
 // }
 			wayPointSet = WP[position];  
}

void Robot::AutonomousPeriodic() {
  //if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
//  } else {
    // Default Auto goes here
 // }
  switch(wayPointSet->command) {
    case AUTO_ANGLE : 
      if(firstAngle) {
        Drive.SetAngle(Drive.GetAngle());
        firstAngle = false;
      }
      Drive.TurnToAngle(wayPointSet->heading);
      if(fabs(wayPointSet->heading - Drive.GetAngle()) < DRIVE_ANGLE_TOLERANCE) { //make store once
       firstAngle = true;
       wayPointSet++;
      }
      break;
    case AUTO_DRIVE :
      Drive.SetDistance(Drive.GetLeftPosition());
      if(firstDrive) {
        firstDrive = false;
        originalDistance = Drive.GetLeftPosition();
      }
      Drive.MoveToDistance(wayPointSet->distance);
      if(fabs(wayPointSet->distance - (Drive.GetLeftPosition() - originalDistance)) < DRIVE_DISTANCE_TOLERANCE) {
        firstDrive = true;
        wayPointSet++;
      }
      break;
    case AUTO_AIM : 
      Drive.Aim(Targeting.ErrorAngle());
      Shooter.Aim(Targeting.Distance());
      if(fabs(Targeting.ErrorAngle()) < ANGLE_TOLERANCE) {
        wayPointSet++;
      }
      break;
    case AUTO_SHOOT : 
      Shooter.ShootFullAuto();
      if(Shooter.Capacity() <= 0) {
        wayPointSet++;
      }
      break;
    case AUTO_STOP :
      Shooter.StopSpin();
      Shooter.StopShooting();
      break;
  }

}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  RunDrive();
  RunShooter();
  RunAim();
  RunIntake();
}

void Robot::TestPeriodic() {}

void Robot::RunDrive() {
  Drive.ManualDrive(-DriverController.GetY(), DriverController.GetX());
 
}
void Robot::RunShooter() {
  double storedShootSpeed = 0;
  if(DriverController.JustPressed(SHOOT)) {
    Shooter.Shoot();
  }
  if(DriverController.JustPressed(SHOOTER_SPIN_MAX)) {
    Shooter.SpinUpMax();
  }
  else if(DriverController.JustPressed(SHOOTER_STOP)) {
    Shooter.StopSpin();
  }
  else if(DriverController.JustPressed(SHOOTER_SPIN_PARTIAL)) {
    Shooter.SpinUpPartial(storedShootSpeed);
  }
  else if(DriverController.GetRawButton(SET_SPEED)) {
    storedShootSpeed = DriverController.GetX();
  }
  
}
void Robot::RunAim() {
  if(DriverController.GetRawButton(AIM)) {
    Drive.Aim(Targeting.ErrorAngle());
    Shooter.Aim(Targeting.Distance());
  }
}

void Robot::RunIntake() {
  double storedIntakeSpeed = 0;
  if(DriverController.JustPressed(INTAKE_SPIN_MAX)) {
    Entry.SpinUpMax();
  }
  else if(DriverController.JustPressed(INTAKE_STOP)) {
    Entry.Stop();
  }
  else if(DriverController.JustPressed(SHOOTER_SPIN_PARTIAL)) {
    Shooter.SpinUpPartial(storedIntakeSpeed);
  }
  else if(DriverController.GetRawButton(SET_SPEED)) {
    storedIntakeSpeed = DriverController.GetX();
  }
  if(DriverController.GetRawButton(UNJAM)) {
    Entry.Unjam();
  }
  else {
    Entry.Stop();
  }
}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
