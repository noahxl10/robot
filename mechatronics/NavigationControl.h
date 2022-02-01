/**
 * @file navigationControl.h
 * @brief Controls the navigation of the robot to the desired position
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 *  So the idea here is to make the robot navigation be relative to a global coordinant 
 * system that we can pass the robot a target x,y,theta and the robot will navigate to
 * autonomously to the target.
 * 
 * The robot pose will be updating the position(pose) of the robot every cycle.
 * Robot pose will include the encoder update and the compass/accelerometer files.
 */

//Include files
#include "robotPoseControl.h" //The robot pose will be the relation of the center of the sample with angle in a global coordinate system
#include "obstacleDetected.h"
#include "globalVariables.h" //Include the global variable list
#include "LineFollow.h"
#include "SharpIR.h"
#include "LEDControl.h"

//Variables Motor Control
double setSpeedLeft = 0.0;
double setSpeedRight = 0.0;
double motorOutLeft = 0.0;
double motorOutRight = 0.0;
double speedLeftGain = 0.0;
double speedRightGain = 0.0;

//Variables for line follow
float Kp = 1.75;
float Kd = 7.8;
float error = 0.0;
float errorPrev = 0.0;
double _LineFollowInterval = 100;
double _LineFollowTimeStamp = 100;

//Variables Line Count
bool oneShot = false;
int lineCount = 0;
double _LineCountDelay1 = 0.0;
double _LineCountDelay2 = 0.0;

int _NavigationState = 0;
double SharpDistance = 0;


int navigationControl(int _NavigationMode)
{
  
  //Navigation Mode
  switch (_NavigationMode)
  {

  case 0:
    robotVel = 0.0;
    robotOmega = 0.0;
    break;

    //Line following
  case 1:
    //Set motor outputs to line follow setpoints
    robotVel = 4.0;
    if (_LineFollowTimeStamp < millis())
    {
      error = ((LinePosition() * 0.000375) - 1.3125);
      robotOmega = Kp * error;
      robotOmega += Kd * (error - errorPrev);
      errorPrev = error;
      _LineFollowTimeStamp = millis() + _LineFollowInterval;
    }
    if (obstacleDetection(true))
    {
      robotVel = 0.0;
      robotOmega = 0.0;
    }
    //Check if sum of the sensors are greater than threshold
    if (getDEN() >= 9000.0 && !oneShot)
    {
      if (_LineCountDelay1 < millis())
      {
        lineCount++;
        oneShot = true;
      }
    }
    else
    {
      _LineCountDelay1 = millis() + 100;
    }
    //Check if sum of the sensors are less than threshold
    if (getDEN() <= 6000.0 && oneShot)
    {
      if (_LineCountDelay2 < millis())
      {
        oneShot = false;
      }
    }
    else
    {
      _LineCountDelay2 = millis() + 100;
    }
    if (lineCount >= 2)
    {
      robotVel = 2.0;
    }
    //If counted 2, robot must be aproaching the sample location
    if (lineCount >= 3)
    {
      _NavigationState = 1;
      robotOmega = 0.0;
    }
    break;

    //Drive Forward Slow
  case 2:
    robotOmega = 0.0;
    _NavigationState = 0;
    lineCount = 0;
    break;
    
  case 3:
    //Navigation to target

    break;
  }

  
  //Velocity control 
  //constrain omega
  if (robotOmega > 4.5)
  {
    robotOmega = 4.5;
  }
  else if (robotOmega < -4.5)
  {
    robotOmega = -4.5;
  }
  
  //Calculate set speed for left and right
  setSpeedLeft = (robotVel + 2.25 * (robotOmega));  //1.5875*
  setSpeedRight = (robotVel - 2.25 * (robotOmega)); //2.25*
  
  //Encoder Gets the velocity in in/sec for the wheel
  encoderUpdate();                                  

  
  //Vel PID using vel from encoders and set speed
  motorOutLeft = VelLeftPID.TargetSpeed(setSpeedLeft, velLeft);
  motorOutRight = VelRightPID.TargetSpeed(setSpeedRight, velRight);
  //Serial.print(setSpeedLeft);
  //Serial.print("  ");
  //Serial.println(velLeft);
  
  // Ensure the ability to stop the robot fast when needed
  if (setSpeedLeft != 0)
  {
    MotorLeft.TargetSpeed(motorOutLeft);
    MotorRight.TargetSpeed(motorOutRight);
  }
  else
  {
    MotorLeft.TargetSpeed(0);
    MotorRight.TargetSpeed(0);
  }

  return _NavigationState;
}
