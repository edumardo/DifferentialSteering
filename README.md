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
The library works with [-127, 127] range, both the input and output methods, i. e., you will need to map your X,Y joystick values to [-127,127] prior the compute, and the result will also be in [-127, 127].

## Joystick library
The example sketch uses the [Joystick library](https://github.com/edumardo/Joystick) I wrote to control with a single dual axis joystick.

## Using the library
In [examples/differentialSteringSingleJoystick.ino](examples/differentialSteringSingleJoystick.ino) yo can see the library in action.

First, initialize a *DifferentialSteering* object with the proper pivot limit:
```
    int fPivYLimit = 32;
    DifferentialSteering DiffSteer;

    void setup () {
        DiffSteer.begin(fPivYLimit);
```
Then, compute differential steering with the joystick outputs. Keep in mind that the inputs of *computeMotors* method have to be mapped to [-127, 127]:
```
    int XValue = map(yourXRaw, yourLowRange, yourHighRange, -127, 127);
    int YValue = map(yourYRaw, yourLowRange, yourHighRange, -127, 127);
    DiffSteer.computeMotors(XValue, YValue);
```
Ultimatelty, do something with motor outputs, like mapping to your desire range (e.g. PWM value). The output range will be [-127, 127]:
```
    int leftMotor = DiffSteer.computedLeftMotor();
    int rightMotor = DiffSteer.computedRightMotor();
```
