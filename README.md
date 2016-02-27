# ArduinoGamepad
A GamePad HID library for Arduino Pro Micro/Leonardo (ATMega32u4)
This library works only on Arduino IDE 1.6.6 or higher!
## How to install
Create a new directory named "Gamepad" in Documents > Arduino > libraries, and copy all files from repository into that directory
## Small example
```c++
//Including a library
#include <Gamepad.h>

//Initializing a Gamepad
Gamepad gp;

int buttonIndex = 0;
bool setState = true;

void setup() {

}

void loop() {
  gp.setButtonState(buttonIndex++, setState);
  if(buttonIndex == 16)
  {
    setState = !setState; //negate the value
    buttonIndex = 0;
  }
  delay(500);
}
```
##How to test gamepad
  - Just try a game what supports a normal GamePad (not X360, if you want to play game whats support only X360, use [X360CE](https://github.com/x360ce/x360ce))
  - Or use a Windows Devices "Tester" (where is option to calibrate a GamePad, but I recommending a Arduinos calibration in example project): Go to Control Panel > Devices and Printers and search your device (for me its a Arduino Leonardo) > Right click > Settings of game device > Properties > Test

##Functions reference

###Gamepad(bool useZRx = false)
Initializing a USB HID Descriptor
  - `boolean` useZRx (default `false`): Z is used to represent the right stick’s X axis, Rx is used to represent the right stick’s Y axis. This doesn’t make sense but this is how most existing USB game pads work. I have tested this using Battlefield Bad Company 2, it works. [SOURCE](http://eleccelerator.com/tutorial-about-usb-hid-report-descriptors/)

###sendUpdate()
Sending a update report, its not needed to use, its executed automatically

###setButtonState(uint8_t button, bool state)
Setting a Button State
  - `uint8_t` button - Number of button (0 - 15), Button #1 is 0, Button #2 is 1 etc...
  - `bool` state - `true` is pressed, `false` is released

###setLeftXaxis(uint8_t axis)
Setting an "axis" for Left Thumbstick X Axis
  - `uint8_t` axis - a value from -127 to 127, when 0 means center (you must format a values from real Thumbsticks to this ranges)

###setLeftYaxis(uint8_t axis)
Setting an "axis" for Left Thumbstick Y Axis
  - `uint8_t` axis - a value from -127 to 127, when 0 means center (you must format a values from real Thumbsticks to this ranges)

###setRightXaxis(uint8_t axis)
Setting an "axis" for Right Thumbstick X Axis
  - `uint8_t` axis - a value from -127 to 127, when 0 means center (you must format a values from real Thumbsticks to this ranges)

###setRightaxis(uint8_t axis)
Setting an "axis" for Right Thumbstick Y Axis
  - `uint8_t` axis - a value from -127 to 127, when 0 means center (you must format a values from real Thumbsticks to this ranges)
  
