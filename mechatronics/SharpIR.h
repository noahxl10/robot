/**
 * @file SharpIR.h
 * @brief Returns the average distance read from the sensor
 * @version 0.1
 * @date 2021-03-31
 * 
 * @copyright Copyright (c) 2021
 * Adapted from noahs PM8 code
 * 
 */
#include "GlobalVariables.h"
int noSamples=5;  
unsigned int senseValue[5] = {0, 0, 0, 0, 0};
float sumOfSamples=0;  
double senseDistance=0;
long _SharpInterval = 20;

 double SharpIR( void )  
 {  

  /////////////////////////////////////////////////////////
  //Sharp (Block Distance Sensor)
  if (_SharpInterval < millis())
  {
    for (byte i = 0; i <= (noSamples-1); i++)
    {
      senseValue[i + 1] = senseValue[i];
    }
    senseValue[0] = analogRead(pinSharpIR);
    sumOfSamples = 0;
    for (byte i = 0; i <= noSamples; i++)
    {
      sumOfSamples += senseValue[i];
    }
    sumOfSamples /= (float)noSamples;
    _SharpInterval = millis() + 30;
  }
  senseDistance = 0;
  senseDistance = (sumOfSamples - 0.0) * (5.0 - 0.0) / (1023 - 0.0) + 0.0; 

  //Not sure where the coeficiencts came from on this data set (Adapted from noahs program)
  //I had to subtract 10 to get it in range of my sensor
  senseDistance = -10 + 2.059*pow(senseDistance,4) - 15.22*pow(senseDistance,3) + 41.49*pow(senseDistance,2) - 51.7*(senseDistance) + 28.4;   
  return senseDistance;  
 }
