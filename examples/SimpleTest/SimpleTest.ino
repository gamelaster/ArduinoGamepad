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