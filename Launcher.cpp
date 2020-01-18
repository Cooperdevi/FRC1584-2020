/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Launcher.h"

Launcher::Launcher() :
ShooterMain(SHOOTER_MAIN), ShooterFollow(SHOOTER_FOLLOW), Trigger(TRIGGER)
{
    ShooterFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, SHOOTER_MAIN);
}

void Launcher::Shoot() {
    TriggerTimer.Reset();
    TriggerTimer.Start();
    if(TriggerTimer.Get() <= TRIGGER_TIME) {
        Trigger.Set(TRIGGER_POWER);
    }
    else {
        TriggerTimer.Stop();
        TriggerTimer.Reset();
    }
}

void Launcher::SpinUpMax() {
    SetSpin(1);
}

void Launcher::SetSpin(double speed) {
    ShooterMain.Set(speed);
}

void Launcher::SpinUpPartial(double speed) {
    SetSpin(speed);
}

void Launcher::StopSpin() {
    SetSpin(0);
}