/**
 * @file MotorControl.cpp
 * @brief DC motor control as part of MotorControl.h
 * @version 0.1
 * @date 2021-02-20
 * 
 */

//Include the Arduino pin library
#include "MotorControl.h"
#include <Arduino.h>

//Create the motor control object
MotorControl::MotorControl(int motorPin1, int motorPin2, int pinPwm)
{
    pinMode(motorPin1, OUTPUT); //Set motor pin1 pinMode
    pinMode(motorPin2, OUTPUT); //Set motor pin2 pinMode
    pinMode(pinPwm, OUTPUT);    //Set Pwm pinMode
    _motorPin1 = motorPin1;     //Set motor pin1 local
    _motorPin2 = motorPin2;     //Set motor pin1 local
    _pinPwm = pinPwm;           //PWM pin
}

//Set target speed and ramp actual speed to the target
void MotorControl::TargetSpeed(int Pwm)
{
    //Contrain the PWM signal to be limited between -255 and 255.
    _pwm = constrain(Pwm, -255, 255);

    //Speed ramp control
    if ((_pwm < Pwm) && (_timeStamp < millis()))
    {
        _pwm++;
        _timeStamp = millis() + _accel;
    }

    else if ((Pwm < _pwm) && (_timeStamp < millis()))
    {
        _pwm--;
        _timeStamp = millis() + _accel;
    }
    
    // If the PWM is positve run FWD
    if ((_pwm >= 1) && (_pwm <= 255))
    {
        digitalWrite(_motorPin1, HIGH);
        digitalWrite(_motorPin2, LOW);
        analogWrite(_pinPwm, map(_pwm, 1, 255, 20, 255));
        _direction = true;
    }

    // Is the PWM value negative, if true go in reverse.
    else if ((_pwm >= -255) && (_pwm <= -1))
    {
        digitalWrite(_motorPin1, LOW);
        digitalWrite(_motorPin2, HIGH);
        analogWrite(_pinPwm, -(map(_pwm, -255, -1, -255, -20)));
        _direction = false;
    }
    else
    {
        digitalWrite(_motorPin1, LOW);
        digitalWrite(_motorPin2, LOW);
        analogWrite(_pinPwm, 0);
        _direction = false;
    }
}

int MotorControl::ActualSpeed()
{
    return _pwm;
}

void MotorControl::SetAccel(int accel)
{
    _accel = accel;
}

bool MotorControl::Direction()
{
    return _direction;
}
