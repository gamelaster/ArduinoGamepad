/*
	Gamepad.cpp
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

#include "Gamepad.h"

#if defined(_USING_HID)

Gamepad::Gamepad()
{	
	static HIDSubDescriptor gamePadDescriptor(ReportDescriptor, sizeof(ReportDescriptor));
	HID().AppendDescriptor(&gamePadDescriptor);
	
	reportData.buttons 		= 0;
	reportData.leftXaxis   	= 0;
	reportData.leftYaxis   	= 0;
	reportData.rightXaxis  	= 0;
	reportData.rightYaxis  	= 0;
}

void Gamepad::setButtonState(uint8_t button, bool state)
{
	if(state == true) bitSet(reportData.buttons, button);
	else bitClear(reportData.buttons, button);
	sendUpdate();
}

void Gamepad::setLeftXaxis (int8_t value)
{
	reportData.leftXaxis = value;
	sendUpdate();
}

void Gamepad::setLeftYaxis (int8_t value)
{
	reportData.leftYaxis = value;
	sendUpdate();
}

void Gamepad::setRightXaxis(int8_t value)
{
	reportData.rightXaxis = value;
	sendUpdate();
}

void Gamepad::setRightYaxis(int8_t value)
{
	reportData.rightYaxis = value;
	sendUpdate();
}

void Gamepad::sendUpdate()
{
	HID().SendReport(0x03, &reportData, sizeof(gamepad_report_struct));
}
#endif