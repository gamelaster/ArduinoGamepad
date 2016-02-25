/*
 * Example of working 2 Gamepads with Calibration
 * Connect first thumbstick X to A1, Y to A0
 *         second thumbstick X to A3,Y to A2
 */
//including a library
#include <Gamepad.h>

//initialize a centers of axises for calibration
int rightXcenter = 500;
int rightYcenter = 500;
int leftXcenter = 500;
int leftYcenter = 500;
double multiplierRX = 0.254; //127 / 500
double multiplierRY = 0.254;
double multiplierLX = 0.254;
double multiplierLY = 0.254;

//Initializing a Gamepad
Gamepad gp;
void setup() {
  //initializing inputs
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  calibrate();
  //pinMode(3,  INPUT_PULLUP);
}

void loop() {
  int lx, ly, rx, ry;
  lx = analogRead(A3);
  ly = analogRead(A2);
  rx = analogRead(A1);
  ry = analogRead(A0);
  //we need to convert a 0-1000 to -127 - 127
  lx = (lx - leftXcenter) * multiplierLX;
  ly = (ly - leftYcenter) * multiplierLY;
  rx = (rx - rightXcenter) * multiplierRX;
  ry = (ry - rightYcenter) * multiplierRY;
  if(lx > 127) lx = 127;
  if(ly > 127) ly = 127;
  if(rx > 127) rx = 127;
  if(ry > 127) ry = 127;
  gp.setLeftXaxis(lx);
  gp.setRightXaxis(rx);
  //because i have placed a thumbstick in breadboard, i must invert a Y axis and swap X and Y axises
  gp.setLeftYaxis(ly);
  gp.setRightYaxis(ry);
  delay(20);
}

void calibrate()
{
  int lx, ly, rx, ry;
  int i = 0;
  while(i < 8)
  {
    lx = analogRead(A3);
    ly = analogRead(A2);
    rx = analogRead(A1);
    ry = analogRead(A0);
    bool validLX = lx > (leftXcenter - 100) && lx < (leftXcenter + 100);
    bool validLY = ly > (leftYcenter - 100) && ly < (leftYcenter + 100);
    bool validRX = rx > (rightXcenter - 100) && rx < (rightXcenter + 100);
    bool validRY = ry > (rightYcenter - 100) && ry < (rightYcenter + 100);
    if(validLX && validLY && validRX && validRY)
    {
      i++;
      //nothing to do here!
    }
    else i = 0;
    delay(20);
  }
  leftXcenter = lx;
  leftYcenter = ly;
  rightXcenter = rx;
  rightYcenter = ry;
  multiplierLX = (double)127 / (double)lx;
  multiplierLY = (double)127 / (double)ly;
  multiplierRX = (double)127 / (double)rx;
  multiplierRY = (double)127 / (double)ry;
}
