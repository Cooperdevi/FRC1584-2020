/*
 * Controller.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: Pirates
 */

#include <DriverInput.h>

DriverInput::DriverInput(int ID) : Joystick(ID), currentPOV(-1) {
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
