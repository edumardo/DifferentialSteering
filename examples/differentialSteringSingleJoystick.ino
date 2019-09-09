#include "Arduino.h"
#include <Joystick.h>

const int serialDelay = 200;
int pinJoystickX = A0;
int pinJoystickY = A1;
int pinJoystickButton = 5;
int noActionLimit = 100;
Joystick joystick(pinJoystickX, pinJoystickY, pinJoystickButton, noActionLimit);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
    // INPUTS (-127..+127)
	int XValue = map(joystick.getXValue(), 0, 1023, -127, 127);
	int YValue = map(joystick.getYValue(), 0, 1023, 127, -127); // (127..-127): YValue decreases when push forward the Y axis.
    bool buttonValue = joystick.getbuttonValue();

    // OUTPUTS
    int     nMotMixL;           // Motor (left)  mixed output           (-128..+127)
    int     nMotMixR;           // Motor (right) mixed output           (-128..+127)

    // CONFIG
    // - fPivYLimt  : The threshold at which the pivot action starts
    //                This threshold is measured in units on the Y-axis
    //                away from the X-axis (Y=0). A greater value will assign
    //                more of the joystick's range to pivot actions.
    //                Allowable range: (0..+127)
    float fPivYLimit = 32.0;

    // TEMP VARIABLES
    float   nMotPremixL;    // Motor (left)  premixed output        (-127..+127)
    float   nMotPremixR;    // Motor (right) premixed output        (-127..+127)
    int     nPivSpeed;      // Pivot Speed                          (-127..+127)
    float   fPivScale;      // Balance scale b/w drive and pivot    (   0..1   )

    // Calculate Drive Turn output due to Joystick X input
    if (YValue >= 0)
    {
        // Forward
        nMotPremixL = (XValue >= 0) ? 127.0 : (127.0 + XValue);
        nMotPremixR = (XValue >= 0) ? (127.0 - XValue) : 127.0;
    } else
    {
        // Reverse
        nMotPremixL = (XValue >= 0) ? (127.0 - XValue) : 127.0;
        nMotPremixR = (XValue >= 0) ? 127.0 : (127.0 + XValue);
    }

    // Scale Drive output due to Joystick Y input (throttle)
    nMotPremixL = nMotPremixL * YValue / 127.0;
    nMotPremixR = nMotPremixR * YValue / 127.0;

    // Now calculate pivot amount
    // - Strength of pivot (nPivSpeed) based on Joystick X input
    // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
    nPivSpeed = XValue;
    fPivScale = (abs(YValue) > fPivYLimit) ? 0.0 : (1.0 - abs(YValue) / fPivYLimit);

    // Calculate final mix of Drive and Pivot
    nMotMixL = (1.0 - fPivScale) * nMotPremixL + fPivScale * ( nPivSpeed);
    nMotMixR = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);

	Serial.print("XValue: "); Serial.print(XValue);
	Serial.print(" | YValue: ");Serial.print(YValue);
    Serial.print(" | nMotMixL: ");Serial.print(nMotMixL);
    Serial.print(" | nMotMixR: ");Serial.print(nMotMixR);
    Serial.println();
	delay(serialDelay);
}
