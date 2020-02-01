/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "VisionProcessing.h"

VisionProcessing::VisionProcessing() :
    DistanceFinder(0)
//angleError(CONSTANT_ANGLE_CHANGE), minForce(MINIMUM_FORCE), angleTolerance(ANGLE_DEADZONE)//, TargetTable(NetworkTableInstance.getDefault().getTable("chameleon-vision").getSubTable("MyCamName"))
{

}


void VisionProcessing::Initialize() {
    auto table = NetworkTable::GetTable("chameleon-vision/MicrosoftLifecamHD3000");
    nt::NetworkTableEntry TargetX = table->GetEntry("yaw");
    nt::NetworkTableEntry TargetY = table->GetEntry("pitch");
    DistanceFinder.startMeasuring();
}

double VisionProcessing::ErrorRange() {
    return TargetX.GetDouble(0);
}

double VisionProcessing::ErrorAngle() {
    return TargetY.GetDouble(0);
}

double VisionProcessing::Distance() {
    return DistanceFinder.getDistance();
}