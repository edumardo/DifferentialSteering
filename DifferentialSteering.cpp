#include "DifferentialSteering.h"

DifferentialSteering::DifferentialSteering(int fPivYLimit)
{
    m_leftMotor = 0;
    m_rightMotor = 0;
    m_fPivYLimit = fPivYLimit;
}

void DifferentialSteering::computeMotors(int XValue, int YValue)
{
    float   nMotPremixL = 0;    // Motor (left)  premixed output        (-127..+127)
    float   nMotPremixR = 0;    // Motor (right) premixed output        (-127..+127)
    int     nPivSpeed = 0;      // Pivot Speed                          (-127..+127)
    float   fPivScale = 0;      // Balance scale b/w drive and pivot    (   0..1   )

    // Calculate Drive Turn output due to Joystick X input
    if (YValue >= 0)
    {
        // Forward
        nMotPremixL = (XValue >= 0) ? COMPUTERANGE : (COMPUTERANGE + XValue);
        nMotPremixR = (XValue >= 0) ? (COMPUTERANGE - XValue) : COMPUTERANGE;
    } else
    {
        // Reverse
        nMotPremixL = (XValue >= 0) ? (COMPUTERANGE - XValue) : COMPUTERANGE;
        nMotPremixR = (XValue >= 0) ? COMPUTERANGE : (COMPUTERANGE + XValue);
    }

    // Scale Drive output due to Joystick Y input (throttle)
    nMotPremixL = nMotPremixL * YValue / COMPUTERANGE;
    nMotPremixR = nMotPremixR * YValue / COMPUTERANGE;

    // Now calculate pivot amount
    // - Strength of pivot (nPivSpeed) based on Joystick X input
    // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
    nPivSpeed = XValue;
    fPivScale = (abs(YValue) > m_fPivYLimit) ? 0.0 : (1.0 - abs(YValue) / m_fPivYLimit);

    // Calculate final mix of Drive and Pivot
    m_leftMotor=   (1.0 - fPivScale) * nMotPremixL + fPivScale * ( nPivSpeed);
    m_rightMotor = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);
}

int DifferentialSteering::computedLeftMotor()
{
    return m_leftMotor;
}
int DifferentialSteering::computedRightMotor()
{
    return m_rightMotor;
}

String DifferentialSteering::toString()
{
    String str = "";
    return (str + "Pivot threshold: " + m_fPivYLimit + " | Left Motor: " + m_leftMotor + " | Right Motor: " + m_rightMotor);
}
