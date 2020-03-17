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
DriverController(0), position(0), wayPointSet(WP4), firstAngle(true), firstDrive(true), //currentSens(sensitivity[sensI]), currentShoot(shootSpeed[shootI]), currentIntake(intakeSpeed[intakeI]),
climbUnlock(false), firstIntake(true), aiming(false), lowSens(false), highSens(false),
autoAngling(false), firstAngling(true), autonomous(false)
//, DriveDisable(false), ShooterDisable(false), AimDisable(false), ClimbDisable(false), IntakeDisable(false)
{
  std::cout << "Start" << std::endl;
  sensI = 9;
  shootI = 9;
  intakeI = 9;
  currentSens = sensitivity[sensI];
  currentShoot = shootSpeed[shootI];
  currentIntake = intakeSpeed[intakeI];
  ShootTimer.Reset();
  FeedTimer.Reset();
}

void Robot::RobotInit() {
  std::cout << "RobotInitT" << std::endl;
 // m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
 // m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
 // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //		frc::SmartDashboard::PutNumber("Auto Select", position);
 // m_positionChooser.InitSendable( );
  m_positionChooser.SetDefaultOption("Default", 4);
  m_positionChooser.AddOption("Left Wall", 3);
  m_positionChooser.AddOption("Right Wall", 0);
  m_positionChooser.AddOption("Power Port", 1);
  m_positionChooser.AddOption("Loading Station", 2);
  frc::SmartDashboard::PutData("Autonomous Selector", &m_positionChooser);

  Targeting.Initialize();
  Entry.Initialize();
  std::cout << "RobotInitB" << std::endl;
  std::cout << "POVCOUNT: " << DriverController.GetPOVCount() << std::endl;
 // Targeting.SwitchMode(true);
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
 // int sensIShow = sensI;// + 1;
 // int shootIShow = shootI;// + 1;
 // int intakeIShow = intakeI;// + 1;
 std::cout << "setting follower" << std::endl;
 //Shooter.SetFollower(); //  ADD BACK
  frc::SmartDashboard::PutNumber("Lidar Distance", Targeting.Distance());
  frc::SmartDashboard::PutNumber("Capacity", Entry.Capacity());
  frc::SmartDashboard::PutNumber("Speed", Drive.GetLeftVelocity() + Drive.GetRightVelocity());
  frc::SmartDashboard::PutBoolean("Targeting Available", Targeting.TargetingAvailable());
  frc::SmartDashboard::PutNumber("Sensitivity", sensI);
  frc::SmartDashboard::PutNumber("Shooter Speed", shootI);
  frc::SmartDashboard::PutNumber("Intake Speed", intakeI);
  frc::SmartDashboard::PutNumber("Left Front", fabs(Drive.GetLeftVelocity()));
  frc::SmartDashboard::PutNumber("Left Rear", fabs(Drive.GetLeftRearVelocity()));
  frc::SmartDashboard::PutNumber("Right Front", fabs(Drive.GetRightVelocity()));
  frc::SmartDashboard::PutNumber("Right Rear", fabs(Drive.GetRightRearVelocity()));
  frc::SmartDashboard::PutData("Gyro", &Drive.Gyro); 
  frc::SmartDashboard::PutNumber("YAW", Targeting.ErrorAngle());
  frc::SmartDashboard::PutNumber("left pos", Drive.GetLeftPosition());
  frc::SmartDashboard::PutNumber("right pos", Drive.GetRightPosition());
  frc::SmartDashboard::PutBoolean("climber", climbUnlock);
  frc::SmartDashboard::PutString("Message", /* Status()*/"PLACEHOLDER"); // TODO add backStatus());
  frc::SmartDashboard::PutBoolean("Indicator 1", false);
  frc::SmartDashboard::PutBoolean("Indicator 2", false);
  frc::SmartDashboard::PutBoolean("Ready to Shoot", (Targeting.ErrorAngle() < ANGLE_TOLERANCE));
  frc::SmartDashboard::PutNumber("Encoder Speed", (Shooter.Speed()));
  frc::SmartDashboard::PutNumber("Encoder Speed Follower", Shooter.FollowerSpeed());

 // Entry.Run(); //ADD BACK
  RunArrays();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartD`ashboard. If you prefer the LstaabVIEW Dashboard,
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
      position = (int) m_positionChooser.GetSelected();

  //if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
 // } else {
    // Default Auto goes here
 // }
 			wayPointSet = WP[position];  
       autonomous = true;
       Targeting.SetClose(true);
}

void Robot::AutonomousPeriodic() {
  std::cout << "COMMAND: " << wayPointSet->command << std::endl << "WAYPOINT: " << wayPointSet << std::endl << "POSITION: " << position << std::endl;
  //if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
//  } else {
    // Default Auto goes here
 // }
  switch(wayPointSet->command) {
    case AUTO_ANGLE : 
      if(firstAngle) {
        Drive.SetAngle();
        firstAngle = false;
      }
      std::cout << "ANGLE SET" << std::endl;
      Drive.TurnToAngle(wayPointSet->heading);
      if(fabs(wayPointSet->heading - Drive.GetAngle()) < DRIVE_ANGLE_TOLERANCE) { //make store once
       firstAngle = true;
       wayPointSet++;
      }
      break;
    case AUTO_DRIVE :
   //   Drive.SetDistance(Drive.GetLeftPosition());
    //  if(firstDrive) {
    //    firstDrive = false;
    //    originalDistance = Drive.GetLeftPosition();
  //    }
      Drive.MoveToDistance(wayPointSet->distance * 780);
      if(fabs(wayPointSet->distance * 780 - Drive.GetLeftPosition()) < DRIVE_DISTANCE_TOLERANCE &&
       fabs(wayPointSet->distance * 780 - Drive.GetRightPosition()) < DRIVE_DISTANCE_TOLERANCE) {
      //  firstDrive = true;
        wayPointSet++;
      }
      break;
    case AUTO_AIM : 
      Drive.Aim(Targeting.ErrorAngle());
      if(fabs(Targeting.ErrorAngle()) < ANGLE_TOLERANCE) {
        Shooter.Aim(Targeting.Distance());
        wayPointSet++;
      }
      break;
    case AUTO_SHOOT : 
      Entry.Feed();
      if(Entry.Capacity() <= 0) {
        wayPointSet++;
      }
      break;
    case AUTO_STOP :
      Shooter.StopSpin();
      Shooter.StopShooting();
      break;
  }

}

void Robot::TeleopInit() {
  Targeting.SetClose(false);
  autonomous = false;
}

void Robot::TeleopPeriodic() {
  //RunDrive();
  //RunShooter();
  //RunAim();
  //RunIntake();
  //RunClimb();

    
 //  std::cout << "YAW: " << Targeting.ErrorAngle() << std::endl << "PITCH: " << Targeting.ErrorRange() << std::endl;
}

void Robot::TestPeriodic() {
  if(DriverController.JustPressedPOV(0)) {
    std::cout << "POV 0 PRESSED" << std::endl;
  }
  else if(DriverController.JustPressedPOV(180)) {
    std::cout << "POV 180 PRESSED" << std::endl;
  }
  Shooter.TestShoot();
  Entry.SpinUpPartial(.2);
 // RunIntake(); //ADD BACK
  //Drive.TestDrive();
  //Entry.TalonTest(DriverController.GetY());
}

void Robot::RunDrive() {
   double turnGain = (DriverController.GetRawButton(RIGHT) ? STEER_GAIN : 0) - (DriverController.GetRawButton(LEFT) ? STEER_GAIN : 0);
   double driveX = fabs(DriverController.GetX()) < .05 ? 0 : DriverController.GetX();
   double driveY = fabs(DriverController.GetY()) < .05 ? 0 : DriverController.GetY();//TODO reimplement angle control
   double driveZ = fabs(DriverController.GetZ()) < .06 ? 0 : DriverController.GetZ();
   driveX += turnGain;
   driveZ += turnGain;
   double driveT = fabs(DriverController.GetThrottle()) < .06 ? 0 : DriverController.GetThrottle();
   crawling = driveX == 0 && driveY == 0 && (driveZ > 0 || driveT > 0);
   if(driveX == 0 && driveY == 0 && driveZ == 0 && driveT == 0 && firstIntake) {
     Drive.SetVelocity(0);
   }
   else if(!climbUnlock && (fabs(driveX) > 0 || fabs(driveY) > 0)) {
     Drive.ManualDrive(driveY * currentSens, driveX * currentSens + turnGain, false);
   //  Drive.ManualDrive(driveY, driveX);
        //Drive.ManualDrive(driveY * currentSens, driveX - (DriverController.GetRawButton(LEFT) ?  STEER_GAIN : 0 ) + (DriverController.GetRawButton(RIGHT) ? STEER_GAIN : 0) * currentSens));

   }
   //#if 0
   else if(!climbUnlock && (DriverController.GetRawButton(SET_ANGLE) || DriverController.JustPressed(SET_ANGLE))) {
     if(DriverController.GetRawButton(SET_ANGLE) && !DriverController.GetRawButton(SENS_ADJUST) && !DriverController.GetRawButton(IN_ADJUST) && !DriverController.GetRawButton(SH_ADJUST)) {
       if(firstAngling) { 
              Drive.SetAngle();
              firstAngling = false;
              autoAngling = true;

       }
       Drive.TurnToAngle(180);
    }
    else {
      firstAngling = true;
      autoAngling = false;
    }  
   }
   else {
     std::cout << "TRYING TO CRAWL: " << driveT << ", " << driveZ << std::endl;
      Drive.ManualDrive(driveT * currentSens * .5, driveZ * currentSens * .5 + MINIMUM_FORCE * DriveTrain::SignOf(driveZ) + turnGain * .2, false);
   }
//#endif

  // if(driveX == 0 || driveY == 0) {
    //
   //  std::cout << driveY << ", " << driveX << ", " << currentSens << std::endl; //done implement speed feedback loop for stopping when released trigger
  //   if(DriverController.GetRawButton(1)) {
    //        Drive.TurnToAngle(45);
            
      //     std::cout << "DISTANCE: " << Targeting.Distance() << std::endl;
   //  }
     //if(DriverController.JustPressed(2)) {
      // Drive.SetAngle();
    // }

 //  }

}
void Robot::RunShooter() {
  /*double storedShootSpeed = 0;
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
  }*/
 
  if(DriverController.JustPressedPOV(SPIN_UP) && !DriverController.GetRawButton(SET_ANGLE)) {
    Shooter.SpinUpPartial(currentShoot);
  }
  else if(DriverController.JustPressedPOV(SPIN_DOWN) && !DriverController.GetRawButton(SET_ANGLE)) {
    Shooter.StopSpin();
  }
  
}
void Robot::RunAim() {
  if(DriverController.GetRawButton(AIM)) {
    //Targeting.SwitchMode(false);
    std::cout << "AIM PRESSED" << std::endl;
    Drive.Aim(Targeting.ErrorAngle());
    aiming = true;
    Targeting.SetLight(1);
  //  Shooter.Aim(Targeting.Distance());
  }
  else {
    aiming = false;
    Targeting.SetLight(0);
    Shooter.Aim(Targeting.Distance());
  }
  if(DriverController.JustPressed(CAMERA)) {
    Targeting.SwitchMode();
    std::cout <<"SWTICH" << std::endl;
  }
}

void Robot::RunIntake() {
 /* double storedIntakeSpeed = 0;
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
  }*/
  #if 0 // TODO NO FUCKIGN WAY THIS WILL WORK FIRST TRY
  if(DriverController.JustPressed(INTAKE_TOGGLE)) {
    Entry.Toggle(currentIntake);
  }
  #endif
  if(FeedTimer.Get() >= FEED_TIME) {
    Entry.Stop();
  }
  if(DriverController.JustPressed(UNJAM)) {
    Entry.Unjam();
  }
  if(ShootTimer.Get() >= .1) {
    Entry.Feed();
  }
  if(DriverController.JustReleased(SHOOT) && ShootTimer.Get() < .1) {
   FeedTimer.Start();
   Entry.Feed();
  }

 if(DriverController.JustPressed(SHOOT)) {\
  ShootTimer.Reset();
  FeedTimer.Reset();
   ShootTimer.Start();
 //   Entry.SwitchState();
    std::cout << "PRESSED SHOOT" << std::endl;
  }

  else { 

    if(!DriverController.GetRawButton(SHOOT)) {
      ShootTimer.Stop();
    //ShootTimer.Reset();
    FeedTimer.Stop();
  //  FeedTimer.Reset();
    }
    if(DriverController.GetRawButton(INTAKE_TOGGLE)) {
      Entry.TakeIn();
    }
    /*
    if(DriverController.GetRawButton(INTAKE_TOGGLE)) {
    Entry.TakeIn();
    if(firstIntake) {
      Targeting.PickSide();
      firstIntake = false;
    }
    Drive.Aim(Targeting.BallErrorX()); //TODO Switching used camera problem; must be fixed
    if(Targeting.BallErrorX() < ANGLE_TOLERANCE) {
      Drive.MoveToDistance(DistanceConvert(Targeting.BallDistance()));
      if(Targeting.BallDistance() > INTAKE_DISTANCE) {
        Drive.ManualDrive(1, 0, false);
      }
    }
  }
  else {
    Entry.Stop();
    firstIntake = true;
  }*/ // ADD BACK
   }

}

 // #endif
 #if 0
  if(DriverController.GetRawButton(INTAKE_TOGGLE)) {
    if(firstIntake) {
      Targeting.PickSide();
      firstIntake = false;
    }
    Drive.Aim(Targeting.BallErrorX()); //TODO Switching used camera problem; must be fixed
    if(Targeting.BallErrorX() < ANGLE_TOLERANCE) {
      Drive.MoveToDistance(DistanceConvert(Targeting.BallDistance()));
      if(Targeting.BallDistance() < INTAKE_DISTANCE) {
        Entry.SpinUpPartial(currentIntake);
        Entry.SwitchState(false);
      }
      else {
        Entry.Stop();
      }
    }
  }
  else {
    firstIntake = true;
  }
  #endif



void Robot::RunArrays() { //TODO fix starting and max
  if(DriverController.GetRawButton(SENS_ADJUST)) {
    if(DriverController.JustPressedPOV(0) && sensI < 9) {
      sensI++;
    //  sensBool[sensI] = 1;
    }
    else if(DriverController.JustPressedPOV(180) && sensI > 0) {
    //  sensBool[sensI] = 0;
      sensI--;
    }
    currentSens = sensitivity[sensI];
  }

  else if(DriverController.GetRawButton(SH_ADJUST)) {
    if(DriverController.JustPressedPOV(0) && shootI < 19) {
      shootI++;
     // shootBool[shootI] = 1;
    }
    else if(DriverController.JustPressedPOV(180) && shootI > 0) {
     // shootBool[shootI] = 0;
      shootI--;
    }
    currentShoot = shootSpeed[shootI];
   }

else if(DriverController.GetRawButton(IN_ADJUST)) {
    if(DriverController.JustPressedPOV(0) && intakeI < 19) {
      intakeI++;
    //  intakeBool[intakeI] = 1;
    }
    else if(DriverController.JustPressedPOV(180) && intakeI > 0) {
    //  intakeBool[intakeI] = 0;
      intakeI--;
    }
    currentIntake = intakeSpeed[intakeI];
   }
  if(sensI <= 2) {
    lowSens = true;
    highSens = false;
  }       
  else if(sensI >= 7) {
    lowSens = false;
    highSens = true;
  }
  else {
    lowSens = false;
    highSens = false;
  }
}

void Robot::RunClimb() {
  if(DriverController.JustPressed(CLIMB_UNLOCK)) {
    climbUnlock = !climbUnlock;
  }
  if(climbUnlock && fabs(DriverController.GetThrottle()) > .05) {
    Climb.Retract(DriverController.GetY());
  }
}

std::string Robot::Status() {
 // const std::string commands[5] = {"AUTO_ANGLE", "AUTO_DRIVE", "AUTO_AIM", "AUTO_SHOOT", "AUTO_STOP"};
// TODO add unjam back
 /*
 Drive: low sensitivity warning, high sens warning, auto angling, crawling, aiming
 Intake: auto picking up, intake on, ball acquired
 Shooter: spin up complete, ready to shoot, spinning up
 Climber: elevating, retracting
 */
  std::string output;
  if(autonomous) {
        switch(wayPointSet->command) {
      case AUTO_ANGLE:
      output = "Autonomous Angling";
      break;
      case AUTO_DRIVE: 
        output = "Autonomous Driving";
        break;
      case AUTO_AIM: 
        output = "Autonomous Aiming";
        break;
      case AUTO_SHOOT:
        output = "Autonomous Shooting";
        break;
      default:
        output = "";
        break;
    }
  }

 

  if(aiming) {
    output = output + "\nAiming";
  }
  if(lowSens) {
    output = output + "\nLow Sensitivity Warning";
  }
  else if(highSens) {
    output = output + "\nHigh Sensitivity Warning";
  }
  if(autoAngling) {
    output = output + "\nAuto Angling";
  }

  if(crawling) {
    output = output + "\nCrawling";
  }
  if(DriverController.GetRawButton(INTAKE_TOGGLE)) { 
    output = output + "\nAuto Collecting";
  }
  if(Targeting.TargetingAvailable()) {
    output = output + "\nTargeting Available";
  }
  if(Targeting.CollectionAvailable()) {
    output = output + "\nCollection Available";
  }
  if(Entry.JustPressedSwitchEntry()) {
    output = output + "\nBall Collected";
  }

  if(climbUnlock) {
    if(DriverController.GetY() > .02) {
      output = output + "\nRaising Climber";
    }
    else if (DriverController.GetY() < -.02) {
      output = output + "\nLowering Climber";
    }
  }
  return output;

}

double Robot::DistanceConvert(double input) {
  return (input + ADD_CONVERT) * MULTIPLY_CONVERT;
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
