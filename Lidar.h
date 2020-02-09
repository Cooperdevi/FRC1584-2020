/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "frc/PIDSource.h"
//#include "frc/PIDSourceType.h"
#include "frc/I2C.h"
//#include "frc/PIDBase.h"
//#include "frc/PIDController.h"
//#include "frc/PIDCommand.h"
//#include "frc/PIDInterface.h"
//#include "frc/PIDOutput.h"
//#include "frc/PIDSubsystem.h"
//#include "frc/SerialPort.h"
//#include "frc/PWM.h"
#include <sstream>
#include "hal/HAL.h"
#include "hal/I2CTypes.h"
#include <chrono>

class Lidar
{
public:
	virtual double getDistance() = 0;
	virtual double PIDGet();
//	virtual ~Lidar();
};

