/**
   @file BezierCurve.h
   @author (you@domain.com)
   @brief This outputs an array of n points along a bezier curve
   @version 0.1
   @date 2021-04-01

   @copyright Copyright (c) 2021

*/
#include "Arduino.h"
#include <math.h>
float Bernstein( int n, int i, float t );

static const float factorialLookup[33] = {
        1.0,
        1.0,
        2.0,
        6.0,
        24.0,
        120.0,
        720.0,
        5040.0,
        40320.0,
        362880.0,
        3628800.0,
        39916800.0,
        479001600.0,
        6227020800.0,
        87178291200.0,
        1307674368000.0,
        20922789888000.0,
        355687428096000.0,
        6402373705728000.0,
        121645100408832000.0,
        2432902008176640000.0,
        51090942171709440000.0,
        1124000727777607680000.0,
        25852016738884976640000.0,
        620448401733239439360000.0,
        15511210043330985984000000.0,
        403291461126605635584000000.0,
        10888869450418352160768000000.0,
        304888344611713860501504000000.0,
        8841761993739701954543616000000.0,
        265252859812191058636308480000000.0,
        8222838654177922817725562880000000.0,
        263130836933693530167218012160000000.0
    };

void BezierCurve( float b[], int bCount, int cpts, float p[] ) {

  int npts = bCount / 2;
  int icount, jcount;
  float step, t;

  // Calculate points on curve
  icount = 0;
  t = 0;
  step = (float)1.0 / ( cpts - 1 );
  for ( int i1 = 0; i1 != cpts; i1++ ) {
    if ( (1.0 - t) < 5e-6 ) {
      t = 1.0;
    }
    jcount = 0;
    p[icount] = 0.0;
    p[icount + 1] = 0.0;
    for ( int i = 0; i != npts; i++ ) {
      float basis = Bernstein( npts - 1, i, t );
      p[icount] += basis * b[jcount];
      p[icount + 1] += basis * b[jcount + 1];
      jcount = jcount + 2;
      Serial.println(p[i]);
    }
    icount += 2;
    t += step;
  }
}

float Bernstein( int n, int i, float t ) {
  float basis;
  float ti; /* t^i */
  float tni; /* (1 - t)^i */

  /* Prevent problems with pow */
  if ( t == 0.0 && i == 0 ) {
    ti = 1.0;
  } else {
    ti = pow( t, i );
  }
  if ( n == i && t == 1.0 ) {
    tni = 1.0;
  } else {
    tni = pow( ( 1 - t ), ( n - i ) );
  }

  float ni;
  float a1 = factorialLookup[n];
  float a2 = factorialLookup[i];
  float a3 = factorialLookup[n-i];
  ni =  a1 / ( a2 * a3 );
  
  //Bernstein basis
  basis = ni * ti * tni;

  return basis;
}













/**
  double posX[n], posY[n];
  posX[0] = 0.0;
  posY[0] = 0.0;
  int i = 0;

  posX[i] = float(x[0]*pow(1-u,3)+3*x[1]*u*pow(1-u,2)+3*x[2]*pow(u,2)*(1-u)+x[3]*pow(u,3));
  posY[i] = float(y[0]*pow(1-u,3)+3*y[1]*u*pow(1-u,2)+3*y[2]*pow(u,2)*(1-u)+y[3]*pow(u,3));
    i++;
**/

/**
  float t = 0;
  float x0, x1, x2, x3;
  float y0, y1, y2, y3;
  x3 = -x[0] + 3*(x[1]-x[2]) + x[3];
  y3 = -y[0] + 3*(y[1]-y[2]) + y[3];
  x2 = 3*(x[0]-2*x[1]+x[2]);
  y2 = 3*(y[0]-2*y[1]+y[2]);
  x1 = 3*(y[1]-x[0]);
  y1 = 3*(y[1]-y[0]);
  x0 = x[0];
  y0 = y[0];
  float dt = 1/(float)n;
  posX[0]=x[0];
  posY[0]=y[0];

  //double dt = 1/(float)n;
  for (int i = 0; i < n; i++){
    float t= (float)i*dt;
    posX[i+1] = ((x3*t+x2)*t+x1)*t + x0;
    posY[i+1] = ((y3*t+y2)*t+y1)*t + y0;

  }

  return;

  }


  /**

  void bezierCurve(int x[] , int y[])
  {
  double xu = 0.0 , yu = 0.0 , u = 0.0 ;
  int i = 0 ;
  for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
  {
      xu = pow(1-u,3)*x[0]+3*u*pow(1-u,2)*x[1]+3*pow(u,2)*(1-u)*x[2]
           +pow(u,3)*x[3];
      yu = pow(1-u,3)*y[0]+3*u*pow(1-u,2)*y[1]+3*pow(u,2)*(1-u)*y[2]
          +pow(u,3)*y[3];
      SDL_RenderDrawPoint(renderer , (int)xu , (int)yu) ;
  }
  }

*/
