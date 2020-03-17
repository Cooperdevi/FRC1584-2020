/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Intake.h"
//#include <dos.h>
//#include <stdio.h>

//#include <conio.h>

Intake::Intake():
IntakeMain(INTAKE_CAN), Test(1), capacity(3), Entry(ENTRY_DIO), Exit(EXIT_DIO), firstTime(true), Conveyor(CONVEYOR_CAN), Compressor(SERVO_PWM), state(true),
Lift(LIFT_CAN), Lock(LOCK_CAN), gotBall(false)//, /* IntakeFollow(INTAKE_FOLLOW), */ Conveyor(CONVEYOR)
{
   /// IntakeFollow.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, INTAKE_MAIN);
  //  Conveyor.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, SHOOTER_MAIN);
    IntakeTimer.Reset();

 
}
void Intake::Initialize() {
   // Conveyor.Set(CONVEYOR_SPEED);
}
void Intake::SpinUpMax() {
    SetIntakeSpeed(1);
}

void Intake::SpinUpPartial(double speed) {
    SetIntakeSpeed(speed);
}

void Intake::Unjam() {
    SetIntakeSpeed(-1);
    Conveyor.Set(-1);
}

void Intake::Stop() {
    SetIntakeSpeed(0);
    Conveyor.Set(0);
    gotBall = false;
    IntakeTimer.Stop();
    IntakeTimer.Reset();
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

void Intake::SwitchState(bool targetState) { //legacy ball lift code
    #if 0
    if(targetState != state) {
        Lock.Set(-1);
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        if(targetState == true) {
            Compressor.SetAngle(COMPRESSED_ANGLE);
            Lift.Set(1);
            state = true;
        }
        else {
            Compressor.SetAngle(UNCOMPRESSED_ANGLE);
            Lift.Set(-1);
            state = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        Lift.Set(0);
        Lock.Set(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        Lock.Set(0);
    }
    #endif
    
}

void Intake::SwitchState() {
    SwitchState(!state);
}

bool Intake::GetState() {
    return state;
}

void Intake::TakeIn() {

    IntakeMain.Set(.3);
    if(JustPressedSwitchEntry()) {
        gotBall = true;
        IntakeTimer.Reset();
        IntakeTimer.Start();
    }

    if(gotBall) {
        Conveyor.Set(FEED_SPEED);
        if(IntakeTimer.Get() >= FEED_TIME) {
            Conveyor.Set(0);
            IntakeTimer.Stop();
        }
    }

}


void Intake::Feed() {
    Conveyor.Set(FEED_SPEED);
}
