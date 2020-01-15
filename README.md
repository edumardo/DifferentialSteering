# Differential Steering with a single dual axis Joystick in Arduino
Just a simple arduino library to use differential steering with two motors. The compute is fully based in the [impulseAdventure](https://www.impulseadventure.com/elec/robot-differential-steering.html) code.

## Install the library & Import
Download this repository as a .zip file and from the Arduino IDE go to *Sketch -> Include library -> Add .ZIP Library*.

You can import the library in your code using the Arduino IDE going to *Sketch -> Include library -> DifferentialSteering*
or directly writing the include statement in your code:
```
#include "DifferentialSteering.h"
```
## Features
*Pending*

## Joystick library
This sketch uses the [Joystick library](https://github.com/edumardo/Joystick) I wrote to control with a single dual axis joystick.

## Using the library
In [examples/differentialSteringSingleJoystick.ino](examples/differentialSteringSingleJoystick.ino) yo can see the library in action.

First, initialize a *DifferentialSteering* object with the proper pivot limit:
```
    int fPivYLimit = 32;
    DifferentialSteering DiffSteer(fPivYLimit);
```
Then, compute differential steering with the joystick outputs:
```
    DiffSteer.computeMotors(XValue, YValue);
```
Ultimatelty, do something with motor outputs, like mapping to your desire range (e.g. PWM value):
```
    int leftMotor = DiffSteer.computedLeftMotor();
    int rightMotor = DiffSteer.computedRightMotor();
```
