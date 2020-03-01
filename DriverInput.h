/*
 * Controller.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Pirates
 */

#pragma once


#include <frc/Joystick.h>
#include <frc/GenericHID.h>
#define MAX_POV_COUNT 5

class DriverInput: public frc::Joystick {
public:
	DriverInput(int ID);
	//virtual ~DriverInput();
	double GetTruePOV();

	//when the button is just pressed
		bool JustPressed(uint32_t ButtonNumber)
		{
			//value of button
			bool CurrentValue = GetRawButton(ButtonNumber);
			//if button is pressed and wasn't before
			bool JustPressed = (CurrentValue && !PressedButtons[ButtonNumber]);
			PressedButtons[ButtonNumber] = CurrentValue;
			return JustPressed;
		}

		//same thing but when button first released
		bool JustReleased(int ButtonNumber)
		{
			bool CurrentValue = GetRawButton(ButtonNumber);
			bool JustReleased = (!CurrentValue && ReleasedButtons[ButtonNumber]);
			ReleasedButtons[ButtonNumber] = CurrentValue;
			return JustReleased;
		}

		bool JustPressedPOV(int POV);
		

	private:
		bool *PressedButtons;
		bool *ReleasedButtons;
	//	bool *PressedPOV;
	//	bool *ReleasedPOV;
		double currentPOV;
		int newPOVCount;
		bool once;
		//bool once[8] = {false, false, false, false, false, false, false, false};//0, 45, 90, 135, 180, 225, 270, 315};
};
