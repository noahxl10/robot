/**
 * @file obstacleDetected.h
 * @brief Returns true whe obstacle in veiw of the sonar (based on input direction).
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "globalVariables.h"
//Variables for Sonar sensor
int sonar1[5] = {0, 0, 0, 0, 0};
int sonar2[5] = {0, 0, 0, 0, 0};
float sonarDist1 = 0;
float sonarDist2 = 0;
int sonarSamples =5;
long _Sonar1Interval = 0;
long _Sonar2Interval = 0;

bool obstacleDetection(bool direction)
{
  // Collect Sonar Data rolling average
  /////////////////////////////////////////////////////////
  //Sonar 1 (Front Sensor)
  if (_Sonar1Interval < millis())
  {
    for (byte i = 0; i < sonarSamples; i++)
    {
      sonar1[i + 1] = sonar1[i];
    }
    sonar1[0] = disFront.ping_cm();
    sonarDist1 = 0;
    for (byte i = 0; i <= sonarSamples; i++)
    {
      sonarDist1 += sonar1[i];
    }
    sonarDist1 /= (float)sonarSamples;
    _Sonar1Interval = millis() + 40;
  }
  
  /////////////////////////////////////////////////////////
  //Sonar 2 (Rear Sensor)
  if (_Sonar2Interval < millis())
  {
    for (byte i = 0; i < sonarSamples; i++)
    {
      sonar2[i + 1] = sonar2[i];
    }
    sonar2[0] = disRear.ping_cm();
    sonarDist2 = 0;
    for (byte i = 0; i <= sonarSamples; i++)
    {
      sonarDist2 += sonar2[i];
    }
    sonarDist2 /= (float)sonarSamples;
    _Sonar2Interval = millis() + 40;
  }

  /////////////////////////////////////////////////////////
  //Detect object in filtered data
  if ((sonarDist1 < 11) && (sonarDist1 > 0) && direction)
  {
    return true;
  }
  else if ((sonarDist2 < 11) && (sonarDist2 > 0) && !direction)
  {
    return true;
  }
  else
  {
    return false;
  }
}
