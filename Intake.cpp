/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Intake.h"

Intake::Intake():
IntakeMain(INTAKE_CAN), Test(1), capacity(3), Entry(ENTRY_DIO), Exit(EXIT_DIO), firstTime(true), Conveyor(CONVEYOR_CAN), Compressor(SERVO_PWM), state(true)//, /* IntakeFollow(INTAKE_FOLLOW), */ Conveyor(CONVEYOR)
{
   /// IntakeFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, INTAKE_MAIN);
  //  Conveyor.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, SHOOTER_MAIN);

 
}
void Intake::Initialize() {
    Conveyor.Set(CONVEYOR_SPEED);
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

void Intake::Toggle(double desired) {
    if(IntakeMain.Get() != desired) {
        SetIntakeSpeed(desired);
    }
    else {
        SetIntakeSpeed(0);
    }
}

void Intake::TalonTest(double test) {
    Test.Set((test + 1) / 2);
}

int Intake::Capacity() {
    return capacity;
}

void Intake::Run() {
    if(JustPressedSwitchEntry()) {
        capacity++;
    } 
    
    if(JustPressedSwitchExit()) {
        capacity--;
    }
    std::cout << "LIMIT SIWTHC: " << Entry.Get() << std::endl;


}

bool Intake::JustPressedSwitchEntry() {
    bool switchStatus = Entry.Get();
    if(switchStatus && firstTime) {
        firstTime = false;
        return true;
    }
    else if(switchStatus && !firstTime) {
        firstTime = true;
        return false;
    }
    return false;
}
bool Intake::JustPressedSwitchExit() {
    bool switchStatus = Exit.Get();
    if(switchStatus && firstTime) {
        firstTime = false;
        return true;
    }
    else if(switchStatus && !firstTime) {
        firstTime = true;
        return false;
    }
    return false;
}

void Intake::SwitchState(bool targetState) {
    if(targetState != state) {
        if(targetState == true) {
            Compressor.SetAngle(COMPRESSED_ANGLE);
            state = true;
        }
        else {
            Compressor.SetAngle(UNCOMPRESSED_ANGLE);
            state = false;
        }
    }
    
}

void Intake::SwitchState() {
    SwitchState(!state);
}

bool Intake::GetState() {
    return state;
}