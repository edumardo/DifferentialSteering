#include "DifferentialStering.h"

DifferentialStering::DifferentialStering(int_fPivYLimit, int minOutputRange, int maxOutputRange)
{
    m_fPivYLimit = int_fPivYLimit;
    m_minOutputRange = minOutputRange;
    m_maxOutputRange = maxOutputRange;
}
int DifferentialStering::getMinOutputRange()
{
    return m_minOutputRange;
}
int DifferentialStering::getMaxOutputRange()
{
    return m_maxOutputRange;
}
int[2] DifferentialStering::getPwmMotors(int XValue, int YValue)
{
    float   nMotPremixL = 0;    // Motor (left)  premixed output        (-127..+127)
    float   nMotPremixR = 0;    // Motor (right) premixed output        (-127..+127)
    int     nPivSpeed = 0;      // Pivot Speed                          (-127..+127)
    float   fPivScale = 0;      // Balance scale b/w drive and pivot    (   0..1   )

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
    pwmMotors[0] = (1.0 - fPivScale) * nMotPremixL + fPivScale * ( nPivSpeed);
    pwmMotors[1] = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);

    return pwmMotors;
}
int DifferentialStering::getPwmLeftMotor()
{
    return pwmMotors[0];
}
int DifferentialStering::getPwmRightMotor()
{
    return pwmMotors[1];
}
String DifferentialStering::toString()
{
    String str = "";
}
void DifferentialStering::toSerial()
{
    Serial.println(toString());
}
