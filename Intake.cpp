/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Intake.h"

Intake::Intake():
IntakeMain(INTAKE_MAIN)//, /* IntakeFollow(INTAKE_FOLLOW), */ Conveyor(CONVEYOR)
{
   /// IntakeFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, INTAKE_MAIN);
  //  Conveyor.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, SHOOTER_MAIN);

 
}

void Intake::SpinUpMax() {
    SetIntakeSpeed(1);
}

void Intake::SpinUpPartial(double speed) {
    SetIntakeSpeed(speed);
}

void Intake::Unjam() {
    SetIntakeSpeed(-1);
}

void Intake::Stop() {
    SetIntakeSpeed(0);
}
