/*
 * tlins_math.hpp
 *
 *  Created on: 24-06-2012
 *      Author: jacek
 */

#ifndef TLINS_MATH_HPP_
#define TLINS_MATH_HPP_

#include <math.h>
#include <stdio.h>

class tlinsMath {
  public:
	static const double PI;
	static const double PI_2;
	static const double PI_1_DIV_2;

	static double *sinCosTable;
	static double *cosTable;
	static double *sinTable;
	static double  dTableSize;
	static double  delta;
	static int     tableSize;

  public:
	static void globalInit(void)
	{
		sinCosTable = nullptr;
		cosTable    = nullptr;
		sinTable    = nullptr;
		dTableSize  = 0.0;
		delta       = 0.0;
		tableSize   = 0;
	}

	static int initSinCosTable(int qSize)
	{
		double delta = 0.0;
		double x     = 0.0;

		tlinsMath::tableSize  = qSize * 4;
		tlinsMath::dTableSize = (double) qSize * 4.0;
		sinCosTable           = new double[tlinsMath::tableSize + qSize + 1];
		if (sinCosTable == (double *) NULL)
			return -1;

		tlinsMath::sinTable = sinCosTable;
		tlinsMath::cosTable = sinCosTable + qSize;

		// Wielkosc kroku
		tlinsMath::delta = tlinsMath::PI_2 / tlinsMath::dTableSize;

		// Budowanie tablicy wyszukiwania
		x = 0.0;
		for (int i = 0; i < tlinsMath::tableSize; i++, x += tlinsMath::delta) {
			tlinsMath::sinTable[i] = sin(x);

			// Piata cwiartka
			if (i < qSize)
				tlinsMath::sinTable[i + qSize * 4] = sin(x);
		}
		return 0;
	}

	static double fSin(double x_)
	{
		if (x_ == 0.0)
			return tlinsMath::sinTable[0];

		double x   = fabs(x_);
		double div = x / tlinsMath::PI_2;

		// Zaokraglanie do zakresu 0 - 2PI
		x = x - tlinsMath::PI_2 * floor(div);

		if (x == tlinsMath::PI_2)
			return tlinsMath::sinTable[tlinsMath::tableSize - 1];

		// Indeks w dol
		double idxD = floor(div * tlinsMath::dTableSize);

		// Indeks
		auto idx = (long) idxD;

		// Wspolczynik nachylenia krzywej
		double a = (tlinsMath::sinTable[idx + 1] - tlinsMath::sinTable[idx]) / tlinsMath::delta;

		// Finalna wartosc SIN
		double res = tlinsMath::sinTable[idx] + a * (x - tlinsMath::delta * idxD);

		if (x_ < 0.0)
			return res * -1.0;

		return res;
	}

	static double fCos(double x_)
	{
		if (x_ == 0.0)
			return tlinsMath::cosTable[0];

		double x = fabs(x_);

		// Zaokraglanie do zakresu 0 - 2PI
		x = x - tlinsMath::PI_2 * floor(x / tlinsMath::PI_2);

		if (x == tlinsMath::PI_2)
			return tlinsMath::cosTable[tlinsMath::tableSize - 1];

		// Indeks w dol
		double idxD = floor(x / tlinsMath::PI_2 * tlinsMath::dTableSize);

		// Indeks
		auto idx = (long) idxD;

		// Wspolczynik nachylenia krzywej
		double a = (tlinsMath::cosTable[idx + 1] - tlinsMath::cosTable[idx]) / tlinsMath::delta;

		// Finalna wartosc SIN
		double res = tlinsMath::cosTable[idx] + a * (x - tlinsMath::delta * idxD);

		if (x_ < 0.0)
			return res * -1.0;

		return res;
	}
};


#endif /* TLINS_MATH_HPP_ */
