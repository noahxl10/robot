/**
 * @file LineFollow.h
 * @brief 
 * @version 0.1
 * @date 2021-03-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 
#include "globalVariables.h" //Include the global variable list
float NUM = 0.0;
float DEN = 0.0;
float SUM = 0.0;
int lineMin[8] = {200, 200, 200, 200, 240, 240, 280, 360};
int lineMax[8] = {2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500};
float qtrCalibrated[NUM_SENSORS];

float LinePosition()
{
    qtrrc.read(sensorValues);
    SUM = 0.0;
    NUM = 0.0;
    DEN = 0.0;
    for (unsigned char i = 0; i < NUM_SENSORS; i++)
    {
        qtrCalibrated[i] = 2500 * ((float)sensorValues[i] - (float)lineMin[i]) / ((float)lineMax[i] - (float)lineMin[i]);
        NUM += (float)qtrCalibrated[i] * i * 1000;
        DEN += (float)qtrCalibrated[i];
    }
    SUM = (NUM / DEN);
    
    return SUM;
    
}

float getDEN(){
    return DEN;
}
