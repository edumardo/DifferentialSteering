#ifndef DifferentialStering_h
#define DifferentialStering_h

#include "Arduino.h"

class DifferentialStering
{
    private:
        int[2] pwmMotors;   //[0] left motor, [1] right motor
        int m_fPivYLimit;
        int m_minOutputRange;
        int m_maxOutputRange;
        const int m_minRange = -127;
        const int m_maxRange = 127;

    public:
        DifferentialStering(int_fPivYLimit, int minOutputRange, int maxOutputRange);
        int getMinOutputRange();
        int getMaxOutputRange();
        int[2] getPwmMotors(int XValue, int YValue);
        int getPwmLeftMotor();
        int getPwmRightMotor();
        String toString();
        void toSerial();
};
#endif
