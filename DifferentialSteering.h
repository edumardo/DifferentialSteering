#ifndef DifferentialSteering_h
#define DifferentialSteering_h

#include "Arduino.h"

class DifferentialSteering
{
    private:
        int m_fPivYLimit;
        int m_leftMotor;
        int m_rightMotor;
        int m_computeRange;

    public:
        DifferentialSteering();
        void begin(int fPivYLimit, int computeRange = 127);
        void computeMotors(int XValue, int YValue);
        int computedLeftMotor();
        int computedRightMotor();
        int getComputeRange();
        String toString();
};
#endif
