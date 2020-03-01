/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "VisionProcessing.h"
#include <iostream>
#include <sstream>
#include <string>
VisionProcessing::VisionProcessing() :
DistanceFinder(LIDAR_DIO), Light(LIGHT_CAN), MainToBackTranslation((units::meter_t)MAIN_TO_BACK, (units::meter_t)0.)
//DistanceFinder(frc::I2C::Port::kOnboard, 0x62)
 //  DistanceFinder(0)
//  DistanceFinder(2, 3)
//angleError(CONSTANT_ANGLE_CHANGE), minForce(MINIMUM_FORCE), angleTolerance(ANGLE_DEADZONE)//, TargetTable(NetworkTableInstance.getDefault().getTable("chameleon-vision").getSubTable("MyCamName"))
{
   /* auto TestTable = NetworkTable::GetTable("test");
    TestTable->SetClientMode();
    TestTable->SetTeam(1584);
    TestTable->SetIPAddress("10.15.84.1");
    TestTable->Initialize();
    TestTable->PutNumber("TEST", 151);*/
   /* inst  = nt::NetworkTableInstance::Create();
    inst.StartClient("10.15.84.61", 5800);
    inst.StartDSClient(5800);

    vision = inst.GetTable("chameleon-vision/Microsoft LifeCam HD-3000");
    
   */
    inst = nt::NetworkTableInstance::GetDefault();
  //  inst2 = nt::NetworkTableInstance::GetDefault();
    vision = inst.GetTable("chameleon-vision/Goal Cam");
    viewing = inst.GetTable("chameleon-vision/Driver Cam");
    ballL = inst.GetTable("chameleon-vision/Ball Cam Left");
    ballR = inst.GetTable("chameleon-vision/Ball Cam Right");
    TargetX = vision->GetEntry("targetYaw");
    TargetY = vision->GetEntry("targetPitch");
    DriverMode = vision->GetEntry("driverMode");
    TargetArea = vision->GetEntry("targetArea");
    ConstDriver = viewing->GetEntry("driverMode");
    BallAreaL = ballL->GetEntry("targetArea");
    BallAreaR = ballR->GetEntry("targetArea");
    BallYawL = ballL->GetEntry("targetYaw");
    BallYawR = ballR->GetEntry("targetYaw");
    BallPitchL = ballL->GetEntry("targetPitch");
    BallPitchR = ballR->GetEntry("targetPitch");
    Pose = vision->GetEntry("Pose");
    

    //IntakeCam.
    //cs::CreateUsbCamera
    //frc::CvSink cvSink = frc::CameraServer::GetInstance().GetVideo();
  //  cs::CvSource outputStream = frc::CameraServer::GetInstance().PutVideo("Blur", 640, 480);



}
//TODO driver mode

void VisionProcessing::Initialize() {
   // table = nt::NetworkTableInstance::GetDefault();
    //cameraTable = NetworkTable::GetTable("chameleon-vision/Microsoft LifeCam HD-3000");
    ConstDriver.SetBoolean(true);

//    DistanceFinder.startMeasuring();
}

double VisionProcessing::ErrorRange() {
    return TargetY.GetDouble(NOT_AVAILABLE);
}

double VisionProcessing::ErrorAngle() {
  #if 0
    return TargetX.GetDouble(NOT_AVAILABLE);
    #endif
    MainToBackTranslation = frc::Translation2d((units::meter_t)MAIN_TO_BACK, (units::meter_t)0.);
    RobotToMainTranslation = frc::Translation2d((units::meter_t)GetPose(0), (units::meter_t)GetPose(1));
    RobotToMainRotation = frc::Rotation2d((units::radian_t)(GetPose(2) * M_PI / 180));
    RobotToMainPose = frc::Pose2d(RobotToMainTranslation, RobotToMainRotation);
    MainToBackTranslation.RotateBy(RobotToMainRotation);
    MainToBackTransformation = frc::Transform2d(MainToBackTranslation, frc::Rotation2d((units::radian_t)0));
    RobotToBackPose = RobotToMainPose + MainToBackTransformation;
    frc::Translation2d temp = RobotToBackPose.Translation();
    return (double)temp.Y();
}

double VisionProcessing::Distance() {
   // std::cout << "DISTANCE: " << DistanceFinder.getDistance() <<std::endl;
   // return DistanceFinder.getDistance() / 2.54;
   frc::Translation2d temp = RobotToBackPose.Translation();
   return (double)temp.Norm();
  //  return DistanceFinder.GetRangeInches();
}

void VisionProcessing::SwitchMode(bool input) {
    DriverMode.SetBoolean(input);
}

void VisionProcessing::SwitchMode() {
    std::cout << "MODE: " << DriverMode.GetBoolean(true) << std::endl;
  //  bool current = DriverMode.GetBoolean(true);
    DriverMode.SetBoolean(!DriverMode.GetBoolean(true));
}

double VisionProcessing::Area() {
    return TargetArea.GetDouble(0);
}

bool VisionProcessing::TargetingAvailable() {
    if(ErrorRange() == NOT_AVAILABLE || ErrorAngle() == NOT_AVAILABLE || Area() < .01) {
        return false;
    }
    return true;
}

bool VisionProcessing::CollectionAvailable() {
  if((BallPitchL.GetDouble(NOT_AVAILABLE) == NOT_AVAILABLE && BallPitchR.GetDouble(NOT_AVAILABLE) == NOT_AVAILABLE) || !(BallAreaL.GetDouble(-1) > .05 || BallAreaR.GetDouble(-1) > .05)) {
    return false;
  }
  return true;
}

void VisionProcessing::PickSide() {
  double LeftDistance = BallPitchL.GetDouble(999999);
  double RightDistance = BallPitchR.GetDouble(999999);
  if(LeftDistance - RightDistance < 2) {
    nearSide = 0;
  }
  else {
    nearSide = (LeftDistance < RightDistance ? -1 : 1);
  }
}

double VisionProcessing::BallErrorX() {
 #if 0
  if(nearSide) { // right side
    return BallYawR.GetDouble(0) + MAX_ERROR;
  }
  else if(!nearSide) {
    return BallYawL.GetDouble(0) - MAX_ERROR;
  }
  return 0;
  #endif
  switch(nearSide) {
    case -1 : 
      return BallYawL.GetDouble(MAX_ERROR) - MAX_ERROR;
      break;
    case 1 :
      return BallYawR.GetDouble(-MAX_ERROR) + MAX_ERROR;
      break;
    case 0 :
      return (BallAreaR.GetDouble(-1) - BallAreaL.GetDouble(-1)) * AREA_TO_YAW;
      break;
  }
  return 0;
  
  
}

double VisionProcessing::BallDistance() {
 // return (nearSide ? BallPitchR.GetDouble(9999999999) : BallPitchL.GetDouble(999999999999999999));
 switch(nearSide) {
   case -1 :
    return BallAreaL.GetDouble(0);
    break;
  case 0 :
    return (BallAreaR.GetDouble(0) + BallAreaL.GetDouble(0));
    break;
  case 1 :
    return BallAreaR.GetDouble(0);
    break;
  default :
    return 0;
    break;
 }
}

void VisionProcessing::SetLight(double set) {
 // if(set > 0) {
  //  set = 0;
  //}
  Light.Set(set);
}

double VisionProcessing::GetPose(int index) {
  return Pose.GetDoubleArray({0, 0, 0})[index];
}