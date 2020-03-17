#pragma once

#include "frc/DigitalInput.h"
#include "frc/Counter.h"
#include "frc/DigitalSource.h"

class LIDARSensor// : public frc::DigitalInput
{
private:
	frc::Counter counter;
	static constexpr double offset = -7.0;
	static constexpr double factor = 100000;
	/* Based on your sensor, you will have different data.
	 * Use multiple data points and a linear regression program
	 * to obtain personal factor and offset values.
	 * for cm: 100000, for in: 39400 (from our testing)
	*/

public:
  LIDARSensor(int channel);

	void LIDARSensorInit();

	double getDistance();
};
