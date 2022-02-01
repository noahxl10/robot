 /*
 * @file PID.h
 * @brief Contructor for the PID object
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef PID_h
#define PID_h

class PID
{
public:
    PID(float kp, float ki, float kd, float interval, float pidMin, float pidMax);
    float TargetSpeed(float, float);
    float ActualSpeed();

private:
    float _Kp, _Ki, _Kd, _Interval, _Min, _Max, _ActualPrev = 0.0;
    double _TimeStamp, _ElapsedTime;
    double  _Error = 0.0, _ErrorPrev1 = 0.0, _Target = 0.0; 
    double _P, _I, _D;   
};
#endif
