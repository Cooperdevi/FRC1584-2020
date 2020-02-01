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
#include "frc/Ultrasonic.h"
#include "LIDARLite_v3.h"

class VisionProcessing {
 public:
  VisionProcessing();
  double ErrorRange();
  double ErrorAngle();
  void Initialize();
  double Distance();
  private:
  std::shared_ptr<NetworkTable> table;
  nt::NetworkTableEntry TargetX, TargetY;
  LIDARLite_v3 DistanceFinder;
 // frc::Ultrasonic DistanceFinder;
 // double /* distanceError,*/ angleError, /*kpDistance,*/ kpAngle, minForce, angleTolerance;

};
