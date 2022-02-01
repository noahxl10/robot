

/**
 * @file blockDetection.h
 * @brief 
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Adafruit_TCS34725.h"
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
const int SAMPLES[][4] ={ {1511, 398, 403, 2106}, {485, 810, 544, 1788}, {437, 512, 797,1700}, {3070, 2756, 2461, 8000}};
const long LUXES[4] = {65376, 689, 128, 1172};
const int interRead[4] = {65374, 730, 55, 824};
double errors[4];
double interError;

int mag1 = 0;
int mag2 = 0;



int blockDetection()
{
  mag1 = analogRead(A10);
  mag2 = analogRead(A11);
     
  if (mag1 > 400 && mag1 < 600 && mag2 > 400 && mag2 < 600) {
    //Mag should be a max of 1023 for analog read of 5V
    uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r , g, b);
    for (int i = 0; i < 4; i++) {
        errors[i] = abs((double(lux) - double(LUXES[i]))/double(LUXES[i]));
    }
    double min_v = 10000.0;
    int min_i = 10000.0;

    for ( int i = 0; i < sizeof(errors)/sizeof(errors[0]); i++ ) {
       if ( errors[i] < min_v ) {
         min_v = errors[i];
         min_i = i;
       }
    }
    if (min_i == 0){
      //Red block detected return 2
      return 2;
    }
    else if (min_i == 1){
      //Green block detected return 3
      return 3;
    }
    else if (min_i == 2){
      //Blue block detected return 4
      return 4;
    }
    else if (min_i == 3){
      //Silver block detected return 5
      return 5;
    }else{
      return 0;
    }
  } else {
    return 1;
  }
  
}
