/***************************************************************************
 *
 *  Programmers and Purdue Email Addresses:
 *  1. deanp@purdue.edu
 *  2. subbiah@purdue.edu
 *  3. hall529@purdue.edu
 *
 *  Lab 02:
 *
 *  Academic Integrity Statement:
 *
 *  We have not used source code obtained from any other unauthorized source,
 *  either modified or unmodified.  Neither have we provided access to our code
 *  to another. The effort we are submitting is our own original work.
 *
 *  Jan 11th, 3:30, SC G073:
 *
 *  Program Description:
 *  The program takes the charge of 3 point charges and calculates the resultant
 *  force on the point charge at the origin.
 *
 ***************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265 // Defining constant pi

// Defining functions for later
double eField(double ptCharge, double r);
double mag(double vecX, double vecY);
double angle(double vecX, double vecY);

double convUnitCToB(double c);
double convUnitMuToB(double Mu);
double convEFieldToForce(double eField, double obsCharge);

int main (void)
{
  double charge1; // Coulombic charge of charge 1 (micro C)
  double charge2; // Coulombic charge of charge 2 (micro C)
  double charge3; // Coulombic charge of charge 3 (micro C)

  double y; // y value of charge 3 (cm)
  double x; // x value of charge 3 (cm)

  double fNetVecX; // Net force vector x comp (N)
  double fNetVecY; // Net force vector y comp (N)
  double fNetMag; // Magnitude of the net force (N)
  double fNetAngle; // Angle of the net force degrees

  double eC2OnC1; // Electric field of charge 2 on 1 (N/C)
  double eC3OnC1; // Electric field of charge 3 on 1 (N/C)

  double fC2OnC1; // Force of charge 2 on 1 (N)
  double fC3OnC1; // Force of charge 3 on 1 (N)

  // Recieving input from user for charges 
  printf("Enter charge [micro-Coulomb] of point #1 -> ");
  scanf("%lf", &charge1);
  printf("Enter charge [micro-Coulomb] of point #2 -> ");
  scanf("%lf", &charge2);
  printf("Enter charge [micro-Coulomb] of point #3 -> ");
  scanf("%lf", &charge3);

  // Recieving input for y and x coordinates of charge 2 and 3
  printf("Enter Y coordinate [cm] of point #2 -> ");
  scanf("%lf", &y);
  printf("Enter X coordinate [cm] of point #3 -> ");
  scanf("%lf", &x);
  printf("\n");

  // Converting micro coulombs to coulombs
  charge1 = convUnitMuToB(charge1);
  charge2 = convUnitMuToB(charge2);
  charge3 = convUnitMuToB(charge3);
  // Converting cm to m
  y = convUnitCToB(y);
  x = convUnitCToB(x);

  // Calculating electric fields and forces from charge 2 and 3
  eC2OnC1 = eField(charge2, y);
  eC3OnC1 = eField(charge3, x);
  fC2OnC1 = convEFieldToForce(eC2OnC1, charge1);
  fC3OnC1 = convEFieldToForce(eC3OnC1, charge1);
  // Finding net force vector and its magnitude and angle
  fNetVecX = fC3OnC1;
  fNetVecY = fC2OnC1;
  fNetMag = mag(fNetVecX, fNetVecY);
  fNetAngle = angle(fNetVecX, fNetVecY);

  // Outputing net force magnitude and angle with the x-axis
  printf("Magnitude of the resultant force on the charge at the origin: %.1f N\n", fNetMag);
  printf("Force vector angle with the x-axis: %.1f degrees\n", fNetAngle);
  return 0;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  eField (Electric Field by Point Charge Calculator)
*
*  Function Return Type:
*  double
*  
*  Parameters (list data type, name, and comment one per line):
*    1. double ptCharge (point charge coulombs)
*    2. double r (distance r from reference point)
*
*  Function Description:
*  This function takes a point charge value in coulombs and its distance from
*  its reference point and returns the electric field generated by the point
*  charge at that point.
*
***************************************************************************/
double eField(double ptCharge, double r)
{
  double k = 8.99 * pow(10, 9); // Defining k as 8.99e9
  double eFieldMag; // Magnitude of electric field
  double rHat = -r / r; // Calculating rHat
  eFieldMag = k * ((ptCharge) / (pow(r, 2))) * rHat;
  return eFieldMag;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  mag (2D Vector Magnitude Calculator)
*
*  Function Return Type:
*  double  
*
*  Parameters (list data type, name, and comment one per line):
*    1. double vec[2] (vector of size 2 to have x and y coords)
*
*  Function Description:
*  This function calculates the magnitude of a vector with x and y coords.
*
***************************************************************************/
double mag(double vecX, double vecY)
{
  double mag; // Magnitude of vector
  mag = sqrt((pow(vecX, 2)) + (pow(vecY, 2)));
  return mag;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  angle (Vector Angle Calculator)
*
*  Function Return Type:
*  double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double vecX (vector X Coordinate)
*    2. double vecY (vector Y Coordinate)
*
*  Function Description:
*  This function returns the angle between a vector with x and y coords.
*
***************************************************************************/
double angle(double vecX, double vecY)
{
  double angle; // Angle of vector by x-axis
  angle = (atan(vecY / vecX) * 180) / PI; // Finding the angle of vector by x-axis
  return angle;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  convUnitCToB (Unit Convertion from Centi to Base)
*
*  Function Return Type:
*  double   
*
*  Parameters (list data type, name, and comment one per line):
*    1. double c (The value of the centi unit)
*
*  Function Description:
*  This function converts a given centi unit to base.
*
***************************************************************************/
double convUnitCToB(double c)
{
  double b; // Base unit
  b = c * pow(10, -2);
  return b;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  convUnitMuToB (Unit Converstion from Micro to Base)
*
*  Function Return Type:
*  double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double Mu (Input unit in micro)
*
*  Function Description:
*  This function converts units from micro to base.
*
***************************************************************************/
double convUnitMuToB(double Mu)
{
  double b; // Base unit
  b = Mu * pow(10, -6);
  return b;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*  convEFieldToForce (Finding Force From Electric Field)
*
*  Function Return Type:
*  double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double eField (Electric Field in Newtons Per Coulomb)
*    2. double obsCharge (Observation Charge in Coulombs)
*
*  Function Description:
*  This function takes the electric field and observation charge given and
*  calculates the force applied by said electric field.
*
***************************************************************************/
double convEFieldToForce(double eField, double obsCharge)
{
  double f; // Force of electric field (N)
  f = eField * obsCharge;
  return f;
}
