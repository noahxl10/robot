/**
 * @file MotorControl.h
 * @brief Creat a motor class with pin define and PWM signal control
 * @version 0.1
 * @date 2021-02-20
 *
 * This class is to create a motor object and control th motor with a ramped PWM signal.
 * The motor direction is controled by a negative/positive PWM signal. The accepted range for PWM is -255 to 255.
 * 
 * TargetSpeed sets the target PWM value
 * ActualSpeed returns the current PWM value
 * Direction returns the current direction, if PWM >= 0 then direction is true.
 * accelMS The ramp time is milliseconds to full speed of 255 PWM
 */

#ifndef MotorControl_h
#define MotorControl_h

class MotorControl
{
public:
    MotorControl(int motorPin1, int motorPin2, int pinPwm);
    void TargetSpeed(int);
    bool Direction();
    int ActualSpeed();
    void SetAccel(int);

private:
    int _motorPin1;
    int _motorPin2;
    int _pinPwm;
    int _pwm;
    bool _direction;
    int _interval;
    long _timeStamp;
    int _accel;
    
};
#endif
