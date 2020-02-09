#pragma once

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
#include <iostream>
#include <chrono>
//#include "frc/hal/I2CJNI.h"

	class LIDARLite_v3 : public frc::PIDSource
	{

	private:
		static constexpr char k_deviceAddress = 0x62;

		HAL_I2CPort m_port;

		//ByteBuffer *const m_buffer = ByteBuffer::allocateDirect(2);
    char m_buffer[2];

	public:


		LIDARLite_v3(frc::I2C::Port *port);

		virtual void startMeasuring();

		virtual void stopMeasuring();

		virtual int getDistance();

	private:
		int writeRegister(int address, int value);

		short readShort(int address);

	public:
		void SetPIDSourceType(frc::PIDSourceType *pidSource);// override;

		frc::PIDSourceType GetPIDSourceType();// override;
//
		double PIDGet() override;
	};

