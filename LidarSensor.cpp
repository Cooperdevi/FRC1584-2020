#include "LidarSensor.h"
#include <iostream>

LIDARSensor::LIDARSensor(int channel):
//counter(frc::Counter::Mode::kSemiperiod) 
counter(channel)
//DigitalInput(channel) 
{
	counter.SetMaxPeriod(1.0);
	//counter.SetUpSource(channel);
//	counter.SetDownSource(channel);
	//counter.SetUpdateWhenEmpty(false);
	counter.SetSemiPeriodMode(true);
	counter.Reset();
}




double LIDARSensor::getDistance()
{
	/*if (counter.Get() < 1)
	{
		return 0.0;
	}*/
	//std::cout << std::endl << "GET: " << counter.Get() <<  std::endl;
	//std::cout << std::endl << "STOPPED: " << counter.GetStopped() << std::endl;
//	std::cout << std::endl << "PERIOD: " << counter.GetPeriod() << std::endl;
	return (counter.GetPeriod() * factor + offset); // Use lin reg to obtain values
}
