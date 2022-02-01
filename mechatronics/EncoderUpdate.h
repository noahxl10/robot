/**
 * @file encoderUpdate.h
 * @brief 
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * if 9.6v = 255 PWM then 159.375 PWM = 6v
 */
#include <Arduino.h>
#include "GlobalVariables.h"
float encRightLast = 0;
float encLeftLast = 0;
long timeStamp = 0; 


void encoderUpdate()
{
    if (timeStamp  <= millis()){
        velLeft = -3.9584 * ((1000.0*((float)(encoderLeft.read() - (float)encLeftLast)/100.0)/12.0)/150.58); 
        encLeftLast = (float)encoderLeft.read();

        velRight = 3.9584 * ((1000.0*((float)(encoderRight.read() - encRightLast)/100.0)/12.0)/150.58); 
        encRightLast = (float)encoderRight.read();

        timeStamp = millis()+ 60;
    }


}
