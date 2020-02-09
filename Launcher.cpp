/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Launcher.h"

Launcher::Launcher() :
ShooterMain(SHOOTER_MAIN), ShooterFollow(SHOOTER_FOLLOW), Trigger(TRIGGER), currentSpeed(0), CapacitySensor(US_PING, US_ECHO), Main(ShooterMain.GetSensorCollection()), Follower(ShooterFollow.GetSensorCollection()), desiredSpeed(0)
{
    ShooterFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, Main.GetQuadratureVelocity());

   // ShooterFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, SHOOTER_MAIN);
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
    currentSpeed = speed;
    desiredSpeed = currentSpeed;
}

void Launcher::SpinUpPartial(double speed) {
    currentSpeed = speed;
    SetSpin(speed);
}

void Launcher::StopSpin() {
    SetSpin(0);
}

void Launcher::Aim(double distance) {
    double power = sqrt((distance * GRAVITY) / (RANGE_PROPORTION * SIN_ANGLE)) / MAX_VELOCITY;
    SetSpin(power); 
    
}

void Launcher::ShootFullAuto() {
    Trigger.Set(TRIGGER_POWER);
}
void Launcher::StopShooting() {
    Trigger.Set(0);
}
int Launcher::Capacity() {
    double distance = CapacitySensor.GetRangeInches();
    int output;
    if(currentSpeed < RUN_SPEED) {
        if(distance > MAX_DIST_5 && distance < MIN_DIST_5) {
            output = 5;
        }
        else if(distance > MIN_DIST_4) {
            output = 4;
        }
        else if(distance > MIN_DIST_3) {
            output = 3;
        }
        else if (distance > MIN_DIST_2) {
            output = 2;
        }
        else {
            output = 1;
        }
        return output;
   }
//implement later.. ultrasonic?
}

void Launcher::SetFollower() {
    /*int mainSpeed = Main.GetQuadratureVelocity();
    int followerSpeed = Follower.GetQuadratureVelocity();
    int speedDifferential = mainSpeed - followerSpeed;
    if(abs(speedDifferential) >  SPEED_TOLERANCE) {
      desiredSpeed += P_SHOOTER * (speedDifferential/MAX_SPEED);
    }
    if(fabs(desiredSpeed) > 1) {
        desiredSpeed = desiredSpeed/fabs(desiredSpeed);
    }
    ShooterFollow.Set(desiredSpeed);*/
    ShooterFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, Main.GetQuadratureVelocity());
}