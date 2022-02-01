/**
 * @file PID.cpp
 * @brief Calculates a simple PID for the provided setpoint and actual. Outputs a floating point value.
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PID.h"
#include <Arduino.h>

PID::PID(float kp, float ki, float kd, float interval, float pidMin, float pidMax)
{
    _Interval = interval;
    
    _Kp = kp;
    _Ki = ki * ((float)_Interval/1000);
    _Kd = kd / ((float)_Interval/1000);
    _Min = pidMin;
    _Max = pidMax;
}

float PID::TargetSpeed(float Setpoint, float Actual)
{
    if (_TimeStamp + _Interval <= millis())
    {
        _TimeStamp = millis();
        _Error = (Setpoint - Actual);
        _P = _Kp *  _Error;
        _I += _Ki * _Error;
        _D = _Kd * (Actual - _ActualPrev);
        
        //Limit the error total
        if (_I > _Max){
          _I = _Max;
        }
        else if (_I < _Min){
          _I = _Min;
        }
        //Combine terms
        _Target = (float)(_P + _I + _D);
        
        //Limit the output
        if (_Target > _Max){
          _Target = _Max;
        }
        else if (_Target < _Min){
          _Target = _Min;
        }
        //Capture Input
        _ActualPrev = Actual;
        
    }
    return _Target;
}
