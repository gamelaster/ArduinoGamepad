/*
	Gamepad.h
	A GamePad HID library for Arduino Pro Micro/Leonardo (ATMega32u4)
	
    Copyright (C) 2016 Marek GAMELASTER Kraus

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "HID.h"

#if defined(_USING_HID)

typedef struct
{
	uint16_t buttons;
	int8_t leftXaxis;
	int8_t leftYaxis;
	int8_t rightXaxis;
	int8_t rightYaxis;
	//TODO: implement a R2 and L2 throttles or what it is
} gamepad_report_struct;

class Gamepad
{
private:
	gamepad_report_struct reportData;
public:
	Gamepad(bool useZRx = false);
	
	void sendUpdate();
	
	void setButtonState(uint8_t button, bool state);
	void setLeftXaxis (int8_t value);
	void setLeftYaxis (int8_t value);
	void setRightXaxis(int8_t value);
	void setRightYaxis(int8_t value);
	
};

#else
	#warning "HID is not supported for this chip"
#endif
#endif