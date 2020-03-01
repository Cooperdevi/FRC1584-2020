/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveTrain.h"

DriveTrain::DriveTrain() :
    frc::DifferentialDrive(lfTalon, rfTalon),
    /*ltTalon(LT_TALON),*/ lfTalon(LF_TALON), rfTalon(RF_TALON), lrTalon(LR_TALON), /*rtTalon(RT_TALON),*/  rrTalon(RR_TALON), left(lfTalon.GetSensorCollection()), right(rfTalon.GetSensorCollection()), leftRear(lrTalon.GetSensorCollection()), rightRear(rrTalon.GetSensorCollection()), looping(false), preventLooping(false),
    angle(NOT_TURNING), aiming(false)
{
    left.SetIntegratedSensorPosition(0);
    right.SetIntegratedSensorPosition(0);
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
   // lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LT_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);
    lfTalon.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);
    rfTalon.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);
    lfTalon.ConfigNominalOutputForward(0, 30);
	lfTalon.ConfigNominalOutputReverse(0, 30);
	lfTalon.ConfigPeakOutputForward(1, 30);
	lfTalon.ConfigPeakOutputReverse(-1, 30);
    lfTalon.Config_kF(0, 0.1097, 30);
	lfTalon.Config_kP(0, 0.125, 30);
	lfTalon.Config_kI(0, 0., 30);
	lfTalon.Config_kD(0, 0., 30);
    rfTalon.ConfigNominalOutputForward(0, 30);
	rfTalon.ConfigNominalOutputReverse(0, 30);
	rfTalon.ConfigPeakOutputForward(1, 30);
	rfTalon.ConfigPeakOutputReverse(-1, 30);
    rfTalon.Config_kF(0, 0.1097, 30);
	rfTalon.Config_kP(0, 0.125, 30);
	rfTalon.Config_kI(0, 0., 30);
	rfTalon.Config_kD(0, 0., 30);
    Gyro.Calibrate();
    Gyro.Reset();
   #if 0
    lfTalon.SetSensorPhase(false);
    lfTalon.SetInverted(false);

    /* Set relevant frame periods to be at least as fast as periodic rate */
    lfTalon.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    lfTalon.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    /* Set the peak and nominal outputs */
    lfTalon.ConfigNominalOutputForward(0, 10);
    lfTalon.ConfigNominalOutputReverse(0, 10);
    lfTalon.ConfigPeakOutputForward(1, 10);
    lfTalon.ConfigPeakOutputReverse(-1, 10);

    /* Set Motion Magic gains in slot0 - see documentation */
    lfTalon.SelectProfileSlot(0, 0);
    lfTalon.Config_kF(0, 0.3, 10);
    lfTalon.Config_kP(0, 0.1, 10);
    lfTalon.Config_kI(0, 0.0, 10);
    lfTalon.Config_kD(0, 0.0, 10);

    /* Set acceleration and vcruise velocity - see documentation */
    lfTalon.ConfigMotionCruiseVelocity(1500, 10);
    lfTalon.ConfigMotionAcceleration(1500, 10);

    /* Zero the sensor */
    lfTalon.SetSelectedSensorPosition(0, 0, 10);
  //  lfTalon.ConfigurePID();
    rfTalon.SetSensorPhase(false);
    rfTalon.SetInverted(false);

    /* Set relevant frame periods to be at least as fast as periodic rate */
    rfTalon.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    rfTalon.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    /* Set the peak and nominal outputs */
    rfTalon.ConfigNominalOutputForward(0, 10);
    rfTalon.ConfigNominalOutputReverse(0, 10);
    rfTalon.ConfigPeakOutputForward(1, 10);
    rfTalon.ConfigPeakOutputReverse(-1, 10);

    /* Set Motion Magic gains in slot0 - see documentation */
    rfTalon.SelectProfileSlot(0, 0);
    rfTalon.Config_kF(0, 0.3, 10);
    rfTalon.Config_kP(0, 0.1, 10);
    rfTalon.Config_kI(0, 0.0, 10);
    rfTalon.Config_kD(0, 0.0, 10);

    /* Set acceleration and vcruise velocity - see documentation */
    rfTalon.ConfigMotionCruiseVelocity(1500, 10);
    rfTalon.ConfigMotionAcceleration(1500, 10);

    /* Zero the sensor */
    rfTalon.SetSelectedSensorPosition(0, 0, 10);
    #endif
}

void DriveTrain::ManualDrive(double magnitude, double direction, bool squared) {
    //ArcadeDrive(magnitude, direction, false);  
    //EndLooping();
    //if(!looping) {
       // std::cout << "GOT DRIVE: " << magnitude << ", " << direction << std::endl;
        magnitude = fabs(magnitude) < 1 ? magnitude : SignOf(magnitude);
        direction = fabs(direction) < 1 ? direction : SignOf(direction);
        if(fabs(GetLeftVelocity() + GetRightVelocity()) / 2 < 10000) {
            ArcadeDrive(magnitude, direction, squared);
        }
        else {
        CurvatureDrive(magnitude, direction, squared);// IsStopped());
        }
  //  }
  //  AllowLooping();
}
/*
void DriveTrain::Adjust(double distance, double angle) {
    //double trueDistance = distance <= MAX_ADJUST_DISTANCE ? distance : MAX_ADJUST_DISTANCE;
    double trueAngle = angle <= MAX_ADJUST_ANGLE ? angle : MAX_ADJUST_ANGLE;
    ArcadeDrive(0, trueAngle);
}*/
void DriveTrain::AutoDrive(double magnitude, double rotateDrive) {
        if(angle != NOT_TURNING)
    {
        double driveRotate = (angle - Gyro.GetAngle())/CLOSE_ANGLE;
        if(fabs(driveRotate) < .1)
        {
            angle = NOT_TURNING;
        }
        else if(driveRotate > TURN_GAIN)
        {
            rotateDrive = TURN_GAIN;
        }
        else if(driveRotate < -TURN_GAIN)
        {
            rotateDrive = -TURN_GAIN;
        }
        else 
        {
            rotateDrive = driveRotate;
        }
    }
   else {
        angle = NOT_TURNING;
    }
    ArcadeDrive(magnitude, rotateDrive, false);
}
void DriveTrain::Aim(double error) {
   #if 0
    double adjust = 0;
    double integral = 0;
    double lastError = 0;
    double derivative = 0;
    if(integral < -INTEGRAL_SATURATION || integral > INTEGRAL_SATURATION) {
        integral = INTEGRAL_SATURATION * (integral/fabs(integral));
    }
    if(error > ANGLE_TOLERANCE) {
        integral += error;
        derivative = error - lastError;
        adjust = P * error + I * integral + D * derivative;//+ MINIMUM_FORCE;
        lastError = error;
    }
 //   EndLooping();
    ArcadeDrive(0, adjust, false);
    #endif 
    std::cout << "ERROR: " << error << std::endl;
    double rotateSpeed;
    if(fabs(error) > ANGLE_TOLERANCE) {
        rotateSpeed = (fabs(error) > ANGLE_TOLERANCE + 1 ? AIM_P * error : 0) + (MINIMUM_FORCE * SignOf(error));
        std::cout << "Rotate Speed: " << rotateSpeed << std::endl;
        ArcadeDrive(0, (fabs(rotateSpeed) < 1 ? rotateSpeed : SignOf(rotateSpeed)), false);
        aiming = true;
    }
    else {
        ArcadeDrive(0, 0, false);
        aiming = false;
    }
    /*double currentAngle = Gyro.GetAngle() - originalAngle;
    double angleDiff = angle - currentAngle;
    double rotateSpeed;
    if(fabs(angleDiff) > DRIVE_ANGLE_TOLERANCE) {
       // std::cout << "ANGLE INCORRECT" << std::endl;
        rotateSpeed = DRIVE_ANGLE_P * angleDiff;
     //   std::cout <<"ROTATE SPEED: (" << rotateSpeed << ", " << angleDiff << ", " << currentAngle << ")" << std::endl;

        ArcadeDrive(0, (fabs(rotateSpeed) < 1 ? rotateSpeed : SignOf(rotateSpeed)), false);
    }
    else {
        ArcadeDrive(0, 0, false);
    //    std::cout << "ANGLE CORRECT" << std::endl;
    }*/

  //  AllowLooping();
}

double DriveTrain::GetLeftPosition() {
    return left.GetIntegratedSensorPosition();
}

double DriveTrain::GetRightPosition() {
    return right.GetIntegratedSensorPosition() ;
}

double DriveTrain::GetLeftVelocity() {
    return left.GetIntegratedSensorVelocity();
}

double DriveTrain::GetRightVelocity() {
    return right.GetIntegratedSensorVelocity();
}

double DriveTrain::GetRightRearVelocity() {
    return rightRear.GetIntegratedSensorVelocity();
}

double DriveTrain::GetLeftRearVelocity() {
    return leftRear.GetIntegratedSensorVelocity();
}

void DriveTrain::TurnToAngle(double angle) {
 //   double originalAngle = GetAngle();
   // EndLooping();
#if 0
    if(fabs((GetAngle() - originalAngle + angle) > DRIVE_ANGLE_TOLERANCE)) { 
        if(angle > 0) { 
            ArcadeDrive(0, DRIVE_ANGLE_P * (angle-originalAngle)/360);
        }
        else {
            ArcadeDrive(0, DRIVE_ANGLE_P * (angle-originalAngle)/360);
        }
    }
    else {
        ArcadeDrive(0, 0);
    }
    #endif
    double currentAngle = Gyro.GetAngle() - originalAngle;
    double angleDiff = angle - currentAngle;
    double rotateSpeed;
    if(fabs(angleDiff) > DRIVE_ANGLE_TOLERANCE) {
       // std::cout << "ANGLE INCORRECT" << std::endl;
        rotateSpeed = DRIVE_ANGLE_P * angleDiff;
     //   std::cout <<"ROTATE SPEED: (" << rotateSpeed << ", " << angleDiff << ", " << currentAngle << ")" << std::endl;

        ArcadeDrive(0, (fabs(rotateSpeed) < 1 ? rotateSpeed : SignOf(rotateSpeed)), false);
    }
    else {
        ArcadeDrive(0, 0, false);
    //    std::cout << "ANGLE CORRECT" << std::endl;
    }
 //   AllowLooping();
}

double DriveTrain::GetAngle() {
    return(fmod(Gyro.GetAngle(), 360));
}

void DriveTrain::SetAngle() {
    originalAngle = Gyro.GetAngle();
    std::cout << "ANGLE SET" << std::endl;
}

void DriveTrain::MoveToDistance(double distance) {
   /* if(fabs(GetLeftPosition() - originalLeftPosition + distance) < DRIVE_DISTANCE_TOLERANCE) {
        if(GetLeftPosition() < distance) {
            ArcadeDrive(fabs(DRIVE_DISTANCE_P * (distance - originalLeftPosition)) < 1 ? DRIVE_DISTANCE_P * (distance - originalLeftPosition) : DRIVE_DISTANCE_P * (distance - originalLeftPosition)/fabs(DRIVE_DISTANCE_P * (distance - originalLeftPosition)), 0, false);
        }
        else {
            ArcadeDrive(fabs(-DRIVE_DISTANCE_P * (distance - originalLeftPosition)) < 1 ? -DRIVE_DISTANCE_P * (distance - originalLeftPosition) : -DRIVE_DISTANCE_P * (distance - originalLeftPosition)/fabs(-DRIVE_DISTANCE_P * (distance - originalLeftPosition)), 0, false);
        }
    }
    else {
        ArcadeDrive(0, 0); 
    }*/
   // if(!preventLooping) {
   // looping = true;
//   	rfTalon.Config_kI(0, 0.02, 30);
//	rfTalon.Config_kD(0, 0.02, 30);
	lfTalon.Config_kP(0, 0.06, 30);
	rfTalon.Config_kP(0, 0.06, 30);
    std::cout << "TRYING TO MOVE : (" << GetLeftPosition() << ", " << GetRightPosition() << ")" << std::endl;
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Position, -distance);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Position, distance);

  //  }
}

void DriveTrain::SetDistance(double distance) {
    originalLeftPosition = distance;
}

void DriveTrain::SetVelocity(double velocity) {
  //  double velocityDiffLeft = GetLeftVelocity() - velocity;
  /*  double velocityDiffRight = GetRightVelocity() - velocity;
    if(fabs(velocityDiffLeft) > VELOCITY_TOLERANCE || fabs(velocityDiffRight) > VELOCITY_TOLERANCE) {
        if(fabs(velocityDiffLeft) > VELOCITY_TOLERANCE) {
            TankDrive(fabs(VELOCITY_P * velocityDiffLeft) < 1 ? VELOCITY_P * velocityDiffLeft : SignOf(velocityDiffLeft), 0., false);
        }
        if(fabs(velocityDiffRight) > VELOCITY_TOLERANCE) {
            TankDrive(0., fabs(VELOCITY_P * velocityDiffRight) < 1 ? VELOCITY_P * velocityDiffRight : SignOf(velocityDiffRight), false);
        }
    }
    else {
        TankDrive(0., 0., false);
    }*/
  //  if(!preventLooping) {
  //  looping = true;
  //	rfTalon.Config_kI(0, 0, 30);
//	rfTalon.Config_kD(0, 0, 30);
	lfTalon.Config_kP(0, 0.125, 30);
	rfTalon.Config_kP(0, 0.125, 30);
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    //lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);
    //rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, velocity);

    //}
    /*if(fabs(GetLeftVelocity() - velocity) > 75) {
        TankDrive(fabs((.005 * (GetLeftVelocity() - velocity)) < 1 ? -(.005 * (GetLeftVelocity() - velocity)) : .005 * (GetLeftVelocity() - velocity)/fabs(.005 * (GetLeftVelocity() - velocity))), 0., false);
    }
    else if(fabs(GetRightVelocity() - velocity) > 75) {
        TankDrive(0., fabs((.005 * (GetRightVelocity() - velocity)) < 1 ? -(.005 * (GetRightVelocity() - velocity)) : .005 * (GetRightVelocity() - velocity) / fabs (.005 * (GetRightVelocity() - velocity))), false);
    }
    else {
        TankDrive(0, 0, false);
    }*/
}

double DriveTrain::SignOf(double input) {
    return input == 0 ? 0 : input/fabs(input);
}

void DriveTrain::EndLooping() {
    preventLooping = true;
    lfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
 //   lrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, LF_TALON);
    //rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RT_TALON);
    rfTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);

  //  rrTalon.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, RF_TALON);  
    looping = false;
}

void DriveTrain::AllowLooping() {
    preventLooping = false;
}


bool DriveTrain::IsStopped() {
    if(GetLeftVelocity() < VELOCITY_TOLERANCE && GetRightVelocity() < VELOCITY_TOLERANCE) {
        return true;
    }
    return false;
}

void DriveTrain::TestDrive() {
    TankDrive(1, 1, false);
}

bool DriveTrain::GetAiming() {
    return aiming;
}

void DriveTrain::MoveToPoint(double point) {
    if(fabs(point) > POINT_TOLERANCE) {
        ArcadeDrive(POINT_P * point, 0, false);
    }
    else {
        ArcadeDrive(0, 0);
        SetVelocity(0);
    }

}