/**
 * @file globalVariables.h
 * @brief This is the global variable list for the robot
 * @version 0.1
 * @date 2021-02-20
 * 
 * 
 * 
 */


/**
 * @file globalVariables.h
 * @brief This is the global variable list for the robot
 * @version 0.1
 * @date 2021-02-20
 * 
 * 
 * 
 */

#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

//LED pins
#define pinRed 40
#define pinGreen 41
#define pinBlue 43

//Sharp Sensor pin
#define pinSharpIR A8

//Sonar Sensor 
#include <NewPing.h>
NewPing disFront(36, 38, 60); //Trigger pin, Echo pin, Max distance [cm]
NewPing disRear(37, 39, 60); //Trigger pin, Echo pin, Max distance [cm]

#include <QTRSensors.h>
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   42    // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7},NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
int qtrMin[] = {204, 196, 200, 160, 236, 200, 240, 280};
int qtrMax[] = {2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500}; 

//Include the PID function
#include "PID.h"
PID VelLeftPID(3.5, 12.5, 0.3, 50.0, -255.0, 255.0); //PID(float kp, float ki, float kd, float interval, float Out Min, float Out Max); - Interval is time in millis till next output update.
PID VelRightPID(3.5, 12.5, 0.3, 50.0, -255.0, 255.0); //PID(float kp, float ki, float kd, int interval, float Out Min, float Out Max); - Interval is time in millis till next output update.

//Include the Arduino library, this allows pinMode setup
#include <Arduino.h>

//DC motor
#include "MotorControl.h"
MotorControl MotorLeft(22, 23, 5);   //MotorControl(Pin1(FWD),Pin2(REV),PWM Pin) - The ramp time is milliseconds to full speed of 255 PWM
MotorControl MotorRight(24, 25, 6); //MotorControl(Pin1,Pin2,PWM Pin) - The ramp time is milliseconds to full speed of 255 PWM

//Servo Motor
#include <Servo.h>
Servo pickServo;


//Encoder pins
#include <Encoder.h> 
Encoder encoderRight(2, 3);
Encoder encoderLeft(18, 19);
double velLeft = 0.0;
double velRight = 0.0;
#include "EncoderUpdate.h" //This updates the velocity and position of the robot

//Other variables 
double robotVel = 0.0;
double robotOmega = 0.0;
double xActual =0;
double yActual =0;
double theta =0;
float posX[20];
float posY[20];

#define gearRatioRight  150.8 //From polulu website 150.58:1 - https://www.pololu.com/product/3076
#define wheelCircum  0.1 //From polulu website diameter = 32mm - https://www.pololu.com/product/1087
#define encoderCount  12.0 //12 Encoder Counts per revolution - https://www.pololu.com/product/4761

#endif
