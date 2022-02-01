/**
 * @file Main.h
 * @brief This block is for the main program
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
//Constantly running programs

//Switch statement programs
#include "navigationControl.h" //Navigation from point A -> B
#include "blockPickUP.h"

//Variables Local
bool _block;
bool _PickUpBlock = false;
int mode = 0;
int destination = 0;
int navigationState = 0;
int navigationComand = 0;
long blockPickupTimeout = 0;

void MainProgram()
{

  //Call pick block function
  
  destination = blockPickUP(_PickUpBlock);

  /**
   * @brief Navigation control
   * 0 stop, 1 linefollow, 2 drive forward slow
   */
  navigationState = navigationControl(navigationComand);
  
  //LED lights set defaults
  bool _redLED = false;
  bool _blueLED = false;
  bool _greenLED = false;
  bool _redFlash = false;
  bool _blueFlash = false;
  bool _greenFlash = false;
  int _redInterval = 500;
  int _blueInterval = 500;
  int _greenInterval = 500;
  
  switch (mode)
  {

  case 0: //Standby mode parked and waiting to have distance sensors blocked to start the program
    _PickUpBlock = false;
    //Flash Green LED to indicate the system is ready
    _greenLED = true;
    _greenFlash = true;
    
    //Wait for run comand
    if (obstacleDetection(true))
    {
      mode = 1;
    }

    break;

  case 1: //Line Follow
    _greenLED = true;
    //line follow
    navigationComand = 1;
    //Wait for two lines to pass
    if (navigationState == 1)
    {
      navigationComand = 2;
      mode = 2;
      blockPickupTimeout = millis();
      
    }
    break;

  case 2: //Drive forward to pick up the block
    if (SharpIR() < 4)
    {
      robotVel = 0.0;
      navigationComand = 0;
      mode = 3;
    }
    break;

  case 3: //Block detection
    navigationComand = 0;
     _PickUpBlock = true;
     Serial.println(destination);
    //Destinations 0 = none, 1=Magnet, 2=Red, 3=Green, 4=Blue, else=Silver
    if (destination == 0){
      break;
    }
    else if (destination == 1)
    {
      _redLED = true;
      _redFlash = true;
      _redInterval = 150;
    }
    else if (destination == 2)
    {
      _redLED = true;
    }
    else if (destination == 3)
    {
      _greenLED = true;
    }
    else if (destination == 4)
    {
      _blueLED = true;
    }
    else
    {
      _redLED = true;
      _blueLED = true;
      _greenLED = true;
    }
    break;

  case 4: //Drive to the target location
    // Stop

    break;

  case 5: //Target reached, set the block down and reverse.
    // Rotate Right

    break;

  case 6: //Drive to the waiting zone, once the line has been detected switch to line following mode
    // Stop

    break;

  case 7: //Line following mode, use the horizontal lines to update the robot encoder position

    break;
  }

  //This is at the end to allow the values to change from defualt above
  LEDControl(pinRed, _redLED, _redFlash, _redInterval);
  LEDControl(pinBlue, _blueLED, _blueFlash, _blueInterval);
  LEDControl(pinGreen, _greenLED, _greenFlash, _greenInterval);
  
}
