#include "Joystick.h"
#include "DifferentialSteering.h"

const int serialDelay = 200;

int pinJoystickX = A0;
int pinJoystickY = A1;
int pinJoystickButton = 5;
int noActionLimit = 16;
int minRange = -127;
int maxRange = 127;
Joystick joystick(pinJoystickX, pinJoystickY, pinJoystickButton, noActionLimit, minRange, maxRange);

int fPivYLimit = 32;
DifferentialSteering DiffSteer;

void setup()
{
    Serial.begin(9600);
    joystick.invertYAxis(); // Y-axis decreases when I push forward in my hardware
    DiffSteer.begin(fPivYLimit);
}

void loop()
{
    int XValue = joystick.getXValue();
    int YValue = joystick.getYValue();
    int lowLimit = joystick.getLowLimit();
    int highLimit = joystick.getHighLimit();

    int leftMotor = 0;
    int rightMotor = 0;

    // Outside no action limit joystick
    if (!((XValue > lowLimit) && (XValue < highLimit) && (YValue > lowLimit) && (YValue < highLimit)))
    {
        DiffSteer.computeMotors(XValue, YValue);
        int leftMotor = DiffSteer.computedLeftMotor();
        int rightMotor = DiffSteer.computedRightMotor();

        // map motor outputs to your desired range

        Serial.println("Differential | " + DiffSteer.toString());
    } else
    {
        Serial.println("idle");
    }

    delay(serialDelay);
}
