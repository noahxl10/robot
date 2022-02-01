/**
 * @file RobotPoseControl.h
 * @brief Robot pose updates the current position of the robot relative to a global frame.
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 */

#include "Lsm303Compass.h" //This code is for the updateing of the compass heading
#include "GlobalVariables.h"

/**
 * The robot omega can be the current angle + the angle between the next two points
 * I think the velocity can be a porportion control for distance of the end point - current location
 * To move along the path the robot can say if the distance to the current point from the actual point is < maybe a 1/2 the robot can index to the next position
 * The setpoint angle will be a PD calculation
 * The velocity setpoint will also be a PD calculation
 */


long _PoseTimeStamp =0;
int _dt = 25;

void robotPoseControl()
{
  if(_PoseTimeStamp > millis()){
    theta += + robotOmega * _dt;
    xActual += robotVel * sin(theta) * _dt;
    yActual += robotVel * cos(theta) * _dt;

    _PoseTimeStamp = (millis() + _dt);
  }
  
  
  
}
