#ifndef DifferentialSteering_h
#define DifferentialSteering_h

#define COMPUTERANGE 127

#include "Arduino.h"

class DifferentialSteering
{
    private:
        // - fPivYLimt  : The threshold at which the pivot action starts
        //                This threshold is measured in units on the Y-axis
        //                away from the X-axis (Y=0). A greater value will assign
        //                more of the joystick's range to pivot actions.
        //                Allowable range: (0..+127)
        int m_fPivYLimit;
        int m_leftMotor;
        int m_rightMotor;

    public:
        DifferentialSteering(int fPivYLimit);
        void computeMotors(int XValue, int YValue);
        int computedLeftMotor();
        int computedRightMotor();
        String toString();
};
#endif
