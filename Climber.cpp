/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber():
ClimberMotor(CLIMBER)
{
    ClimberMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyClosed);
}

void Climber::Release() {
 //to be implemented 
}

void Climber::Retract(double speed) {
    ClimberMotor.Set(speed);
}
