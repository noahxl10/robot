
#include <math.h>
#include "BezierCurve.h"
//The bezier calculation only needs to run one time based on these locations
//Navigation to the desired drop location x,y locations 
//                         Location A    Location B    Location C    Location D  Location E    
float bezierPosX[5][4] = {{18,25,32,32},{18,25,32,32},{18,25,25,18},{18,10,4,4},{18,10,4,4}};
float bezierPosY[5][4] = {{32,32,25,22},{32,32,25,12},{32,32,7,7},{32,32,25,22},{32,32,25,12}};
//[Start location, midpoint 1, midpoint 2, End Location]

int bezierPoints =30; //Should be less than 30 points along the path. The playmat is 36x36 so max distance is about 51 inches

void robotSetup()
{
  //Serial Setup
  Serial.begin(115200);

  /**
  //Calculate the bezier curves for the provided location arrays
  float x[bezierPoints][5];
  float y[bezierPoints][5];
  float bezierArrayInputX[4];
  float bezierArrayInputY[4];
  for(int j = 0; j < 5; j++){
    //Points to calculate is a function of the distance to travel
    bezierPoints = int(sqrt(pow((bezierPosX[j][3]-bezierPosX[j][0]),2)+pow((bezierPosY[j][3]-bezierPosY[j][0]),2))/2.0);
    Serial.println(bezierPoints);
    for(int k =0;k < 4;k++){
      bezierArrayInputX[k] = bezierPosX[j][k];
      bezierArrayInputY[k] = bezierPosY[j][k];
      Serial.print(bezierArrayInputX[k]);
      Serial.print("   ");
      Serial.println(bezierArrayInputY[k]);
    }
    //BezierCurve( float b[], int bCount, int cpts, float p[] )
    BezierCurve(bezierArrayInputX, 4, 2, bezierArrayInputY);
    for (int i = 0; i < bezierPoints; i++){
      x[i][j] = posX[i];
      y[i][j] = posY[i];
      Serial.print(posX[i]);
      Serial.print("   ");
      Serial.println(posY[i]);
    }
    
  }
  **/
  //Servo Setup
  pickServo.attach(9);

  //Sensor Setup
  pinMode(A8, INPUT); // Distance Sensor

  //Other Setup
  MotorLeft.SetAccel(1);
  MotorRight.SetAccel(1);

  //LED Setup
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);


  //Adafruit Magnometer
  mag.enableAutoRange(true);
}
