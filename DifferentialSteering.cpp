#include "DifferentialSteering.h"

/**
 *  Constructor class.
 */
DifferentialSteering::DifferentialSteering() {
    m_leftMotor = 0;
    m_rightMotor = 0;
    m_computeRange = 127;
}

/**
 * Initialize the threshold at which the pivot action starts.
 *
 * @param fPivYLimit: Threshold. Is measured in units on the Y-axis away from the X-axis (Y=0).
 *                    A greater value will assign more of the joystick's range to pivot actions.
 *                    Allowable range: (0..+m_computeRange).
 */
void DifferentialSteering::begin(int fPivYLimit, int computeRange = 127) {
    m_fPivYLimit = fPivYLimit;
    m_computeRange = computeRange;
}

/**
 * Compute differential steering from (x,y) values.
 *
 * @param XValue: X value in [-m_computeRange, m_computeRange] range.
 * @param YValue: Y value in [-m_computeRange, m_computeRange] range.
 */
void DifferentialSteering::computeMotors(int XValue, int YValue) {
    float   nMotPremixL = 0;    // Motor (left)  premixed output        (-m_computeRange...+m_computeRange)
    float   nMotPremixR = 0;    // Motor (right) premixed output        (-m_computeRange...+m_computeRange)
    int     nPivSpeed = 0;      // Pivot Speed                          (-m_computeRange...+m_computeRange)
    float   fPivScale = 0;      // Balance scale b/w drive and pivot    (   0..1   )

    // Calculate Drive Turn output due to Joystick X input
    if (YValue >= 0) {
        // Forward
        nMotPremixL = (XValue >= 0) ? m_computeRange : (m_computeRange + XValue);
        nMotPremixR = (XValue >= 0) ? (m_computeRange - XValue) : m_computeRange;
    } else {
        // Reverse
        nMotPremixL = (XValue >= 0) ? (m_computeRange - XValue) : m_computeRange;
        nMotPremixR = (XValue >= 0) ? m_computeRange : (m_computeRange + XValue);
    }

    // Scale Drive output due to Joystick Y input (throttle)
    nMotPremixL = nMotPremixL * YValue / m_computeRange;
    nMotPremixR = nMotPremixR * YValue / m_computeRange;

    // Now calculate pivot amount
    // - Strength of pivot (nPivSpeed) based on Joystick X input
    // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
    nPivSpeed = XValue;
    fPivScale = (abs(YValue) > m_fPivYLimit) ? 0.0 : (1.0 - abs(YValue) / m_fPivYLimit);

    // Calculate final mix of Drive and Pivot
    m_leftMotor  = (1.0 - fPivScale) * nMotPremixL + fPivScale * ( nPivSpeed);
    m_rightMotor = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);
}

/*
 * Returns the value of the left motor computed in computeMotors method.
 *
 * @return left computed motor, in [-m_computeRange, m_computeRange] range.
 */
int DifferentialSteering::computedLeftMotor() {
    return m_leftMotor;
}

/*
 * Returns the value of the right motor computed in computeMotors method.
 *
 * @return right computed motor, in [-m_computeRange, m_computeRange] range.
 */
int DifferentialSteering::computedRightMotor() {
    return m_rightMotor;
}

/**
 * Return the compute range used in the computeMotors method.
 * 
 * @return the compute range.
 */
int DifferentialSteering::getComputeRange() {
    return m_computeRange;
}

/*
 * Returns information about current computed motors and pivot threshold.
 * 
 * @return a string with the information.
 */
String DifferentialSteering::toString() {
    String str = "";
    return (str + "Pivot threshold: " + m_fPivYLimit + " | Compute range: " + m_computeRange + " | Left Motor: " + m_leftMotor + " | Right Motor: " + m_rightMotor);
}
