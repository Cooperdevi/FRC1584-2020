/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */

#include <stdexcept>
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
#include "Lidar.h"
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//#include <dos.h>
//#include <windows.h>

class LidarI2C : public Lidar
{
public:
	LidarI2C(frc::I2C::Port port, char address);
	virtual double getDistance();
	virtual double PIDGet();
//	virtual ~LidarI2C();
private:
	frc::I2C *lidar;
	void readyUp();
	/**
	 * Pin 1 - 5v
	 * Pin 2 - Power en - Digital output - turn off sensor (low) turn on sensor (high)
	 * Pin 3 - Modeline - Digital input - finding how long pulsed high
	 * Pin 3 - Resistor line - trigger - Digital output - set low for continuous read
	 * Pin 6 - GND
	 */
};
