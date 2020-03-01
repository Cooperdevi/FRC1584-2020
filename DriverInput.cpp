/*
 * Controller.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: Pirates
 */

#include <DriverInput.h>

DriverInput::DriverInput(int ID) : Joystick(ID), currentPOV(-1), once(false)
	    {


		int ButtonCount = GetButtonCount();
	    PressedButtons = new bool [ButtonCount + 1];
	    ReleasedButtons = new bool [ButtonCount + 1];

	    //add list of buttons to an array
	    for(int bnum = 0; bnum <= ButtonCount; bnum ++)
	    {
	    	PressedButtons[bnum] = false;
	    	ReleasedButtons[bnum] = false;
	    }

}

double DriverInput::GetTruePOV() {
	double newPOV = Joystick::GetPOV();
	if (newPOV != currentPOV) {
		if (++newPOVCount > MAX_POV_COUNT) {
			currentPOV = newPOV;
		}
	}
	else {
		newPOVCount = 0;
	}
	return currentPOV;
}

bool DriverInput::JustPressedPOV(int POV) {
/*	beingPressed = GetPOV() != -1;
	if(beingPressed) {
		checkingPOV = GetPOV();
	}*/
	bool currentValue = GetPOV() == POV;
	if(currentValue && !once) {
		once = true;
		return true;
	}
	else if(GetPOV() == -1) {
		once = false;
		return false;
	}
	return false;


			//value of button
			/*bool CurrentValue = GetPOV() == POV;
			bool output = false;
			if(CurrentValue && POV != checkingPOV) {
				output = true;
			}*/

			//int iPOV = GetPOV() / 45;
			//bool output = false;
			/*//if button is pressed and wasn't before
			bool JustPressed = (CurrentValue && !PressedPOV[0]);
			
			PressedPOV[0] = CurrentValue;*/
			//checkingPOV = POV;
		//	return output;
			/*if(!CurrentValue) { 
				once = false;
				return false;
			}
			else if(CurrentValue && !once) {
				once = true;
				return true;
			}

			return false;*/
}


