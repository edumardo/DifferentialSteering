#ifndef DifferentialSteering_h
#define DifferentialSteering_h

#define COMPUTERANGE 127

#include "Arduino.h"

class DifferentialSteering
{
    private:
        int m_fPivYLimit;
        int m_leftMotor;
        int m_rightMotor;

    public:
        DifferentialSteering();
        void begin(int fPivYLimit);
        void computeMotors(int XValue, int YValue);
        int computedLeftMotor();
        int computedRightMotor();
        int getComputeRange();
        String toString();
};
#endif
