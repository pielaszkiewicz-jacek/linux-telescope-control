/*
 * tlins_math.cpp
 *
 *  Created on: 24-06-2012
 *      Author: jacek
 */

#include <math.h>
#include <tlins_math.hpp>

const double tlinsMath::PI         = 3.141592653589793238462643383279;
const double tlinsMath::PI_2       = 2.0 * 3.141592653589793238462643383279;
const double tlinsMath::PI_1_DIV_2 = 1.0 / (2.0 * 3.141592653589793238462643383279);

double *tlinsMath::sinCosTable;
double *tlinsMath::cosTable;
double *tlinsMath::sinTable;
double  tlinsMath::dTableSize;
double  tlinsMath::delta;
int     tlinsMath::tableSize;
