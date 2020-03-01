/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "OurDefines.h"
#include "ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h"
#include "frc/Ultrasonic.h"
//#include "LIDARLite_v3.h"
//#include "LidarI2C.h"
//#include "Lidar.h"
#include "LidarSensor.h"
#include "frc/geometry/Pose2d.h"
#include "frc/geometry/Transform2d.h"
#include "frc/geometry/Translation2d.h"
#include "frc/geometry/Rotation2d.h"
//#include "cameraserver/CameraServer.h"

class VisionProcessing {
 public:
  VisionProcessing();
  double ErrorRange();
  double ErrorAngle();
  void Initialize();
  double Distance();
  void SwitchMode(bool input);
  void SwitchMode();
  bool TargetingAvailable();
  double Area();
  void PickSide();
  double BallErrorX();
  double BallDistance();
  bool CollectionAvailable();
  void SetLight(double set);
  void Run();
  double GetPose(int index);
 // void TestDrive();
  private:
  std::shared_ptr<NetworkTable> vision, viewing, ballL, ballR;
  nt::NetworkTableInstance inst;//, inst2;
 // nt::NetworkTable cameraTable;
  nt::NetworkTableEntry TargetX, TargetY, DriverMode, TargetArea, ConstDriver, BallAreaL, BallAreaR, BallYawL, BallYawR, BallPitchL, BallPitchR, Pose;
  LIDARSensor DistanceFinder;
  int nearSide; //false for left, true for right]; -1 for left, 0 for both, 1 for right
ctre::phoenix::motorcontrol::can::WPI_VictorSPX Light;
  frc::Translation2d RobotToMainTranslation, MainToBackTranslation;
  frc::Rotation2d RobotToMainRotation;
  frc::Transform2d MainToBackTransformation;
  frc::Pose2d RobotToMainPose, RobotToBackPose;

 // cs::UsbCamera IntakeCam = frc::CameraServer::GetInstance()->StartAutomaticCapture();
 //// nt::NetworkTable* TestTable;

 // LidarI2C DistanceFinder;
//  LIDARLite_v3 DistanceFinder;Lidar
 // frc::Ultrasonic DistanceFinder;
 // double /* distanceError,*/ angleError, /*kpDistance,*/ kpAngle, minForce, angleTolerance;

};
