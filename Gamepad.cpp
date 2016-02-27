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

Gamepad::Gamepad(bool useZRx)
{
	if(useZRx)
	{
		static const uint8_t ReportDescriptor[] PROGMEM = {
			0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
			0x09, 0x05,                    // USAGE (Game Pad)
			0xa1, 0x01,                    // COLLECTION (Application)
			0xa1, 0x00,                    //   COLLECTION (Physical)
			0x85, 0x03,                	   //     REPORT_ID (3)
			0x05, 0x09,                    //     USAGE_PAGE (Button)
			0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
			0x29, 0x10,                    //     USAGE_MAXIMUM (Button 16)
			0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
			0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
			0x75, 0x01,                    //     REPORT_SIZE (1)
			0x95, 0x10,                    //     REPORT_COUNT (16)
			0x81, 0x02,                    //     INPUT (Data,Var,Abs)
			0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
			0x09, 0x30,                    //     USAGE (X)
			0x09, 0x31,                    //     USAGE (Y)
			0x09, 0x32,                    //     USAGE (Z)
			0x09, 0x33,                    //     USAGE (Rx)
			0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
			0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
			0x75, 0x08,                    //     REPORT_SIZE (8)
			0x95, 0x04,                    //     REPORT_COUNT (4)
			0x81, 0x02,                    //     INPUT (Data,Var,Abs)
			0xc0,                          //     END_COLLECTION
			0xc0                           // END_COLLECTION
		};
		static HIDSubDescriptor gamePadDescriptor(ReportDescriptor, sizeof(ReportDescriptor));
		HID().AppendDescriptor(&gamePadDescriptor);
	}
	else
	{
		static const uint8_t ReportDescriptor[] PROGMEM = {
			0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
			0x09, 0x05,                    // USAGE (Game Pad)
			0xa1, 0x01,                    // COLLECTION (Application)
			0xa1, 0x00,                    //   COLLECTION (Physical)
			0x85, 0x03,                	   //     REPORT_ID (3)
			0x05, 0x09,                    //     USAGE_PAGE (Button)
			0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
			0x29, 0x10,                    //     USAGE_MAXIMUM (Button 16)
			0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
			0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
			0x75, 0x01,                    //     REPORT_SIZE (1)
			0x95, 0x10,                    //     REPORT_COUNT (16)
			0x81, 0x02,                    //     INPUT (Data,Var,Abs)
			0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
			0x09, 0x30,                    //     USAGE (X)
			0x09, 0x31,                    //     USAGE (Y)
			0x09, 0x33,                    //     USAGE (Rx)
			0x09, 0x34,                    //     USAGE (Ry)
			0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
			0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
			0x75, 0x08,                    //     REPORT_SIZE (8)
			0x95, 0x04,                    //     REPORT_COUNT (4)
			0x81, 0x02,                    //     INPUT (Data,Var,Abs)
			0xc0,                          //     END_COLLECTION
			0xc0                           // END_COLLECTION
		};
		static HIDSubDescriptor gamePadDescriptor(ReportDescriptor, sizeof(ReportDescriptor));
		HID().AppendDescriptor(&gamePadDescriptor);
	}
	
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