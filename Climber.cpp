/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber():
ClimberMotor(CLIMBER), ClimberSensor(ClimberMotor.GetSensorCollection()), Follower(CLIMBER_FOLLOW)
{
    ClimberMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyClosed);
    ClimberMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::SoftwareEmulatedSensor);
    Follower.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, CLIMBER);
  ////  ClimberSensor = (ClimberMotor.GetSensorCollection());
}

void Climber::Release() {
 //to be implemented 
}

void Climber::Retract(double speed) {
    if(speed > 0 && ClimberMotor.GetSelectedSensorPosition() == TOP_POSITION) {
        speed = 0;
    }
    ClimberMotor.Set(speed);
}
