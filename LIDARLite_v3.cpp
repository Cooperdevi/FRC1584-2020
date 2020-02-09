#include "LIDARLite_v3.h"


	LIDARLite_v3::LIDARLite_v3(frc::I2C::Port *port):  
     m_port(HAL_I2CPort::HAL_I2C_kOnboard) 
	{
        int32_t *status;
		HAL_InitializeI2C(m_port, status);
	}

	void LIDARLite_v3::startMeasuring()
	{
		writeRegister(0x04, 0x08 | 32); // default plus bit 5
		writeRegister(0x11, 0xff);
		writeRegister(0x00, 0x04);
	}

	void LIDARLite_v3::stopMeasuring()
	{
		writeRegister(0x11, 0x00);
	}

	int LIDARLite_v3::getDistance()
	{
		return readShort(0x8f);
	}

	int LIDARLite_v3::writeRegister(int address, int value)
	{
		m_buffer[0] = (static_cast<char>(address));
		m_buffer[1] = (static_cast<char>(value));

		return HAL_WriteI2C(m_port, k_deviceAddress, (uint8_t*)(m_buffer), static_cast<char>(2));
	}

	short LIDARLite_v3::readShort(int address)
	{
		m_buffer[0] = static_cast<char>(address);
		HAL_WriteI2C(m_port, k_deviceAddress, (uint8_t*)(m_buffer), static_cast<char>(1));
		HAL_ReadI2C(m_port, k_deviceAddress, (uint8_t*)(m_buffer), static_cast<char>(2));
       // m_buffer->pubseekpos(0);
		return static_cast<short>(m_buffer[0]);
	}

	void LIDARLite_v3::SetPIDSourceType(frc::PIDSourceType *pidSource)
	{
		if (*pidSource != frc::PIDSourceType::kDisplacement)
		{
			throw std::invalid_argument("Only displacement is supported");
		}
	}

	frc::PIDSourceType LIDARLite_v3::GetPIDSourceType()
	{
		return frc::PIDSourceType::kDisplacement;
	}

	double LIDARLite_v3::PIDGet()
	{
		return getDistance();
	}

