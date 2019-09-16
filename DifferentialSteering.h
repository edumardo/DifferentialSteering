#ifndef DifferentialSteering_h
#define DifferentialSteering_h

#define COMPUTERANGE 127

#include "Arduino.h"

class DifferentialSteering
{
    private:
        int m_fPivYLimit;
        int leftMotor;
        int rightMotor;

    public:
        DifferentialSteering(int fPivYLimit);
        void computeMotors(int XValue, int YValue);
        int computedLeftMotor();
        int computedRightMotor();
        String toString();
        void toSerial();
};
#endif
