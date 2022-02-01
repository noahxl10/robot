/**
   @file blockPickUP.h
   @brief Write the target value for the servo to pick up the block
   @version 0.1
   @date 2021-02-20

    This function takes in bool to enable the write of the target position to the servo.
    The variable for the desired angle will need to be configured.
*/

#include "BlockDetection.h" //This code is for the detection and destination of the sample block

int targetAngle = 70; //This variable will need to be configured 
bool colorOneShot =false;
long colorReadDelay = 0;
int blockPickUP(bool pickBlock)
{
  //Cycle the servo to the target position
  if(pickBlock){
      pickServo.write(targetAngle);
      if (!colorOneShot){
        colorReadDelay = millis();
        colorOneShot = true;
      }
      if ((colorReadDelay + 500) > millis()){
        return blockDetection();
      }
  } else{
      pickServo.write(0);
      colorOneShot = false;
      return 0;
  }

  
}
