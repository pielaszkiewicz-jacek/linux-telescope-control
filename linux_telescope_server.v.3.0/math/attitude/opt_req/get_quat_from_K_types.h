/*
 * File: get_quat_from_K_types.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 10-Jul-2021 11:13:20
 */

#ifndef GET_QUAT_FROM_K_TYPES_H
#define GET_QUAT_FROM_K_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct0_T
#define typedef_struct0_T

struct struct0_T {
	float w[3];
	float r[6];
	float b[6];
	float Mu_noise_var;
	float Eta_noise_var;
	float dT;
	float K[16];
	float P[16];
	float mk;
	float Rho;

	struct0_T &operator=(struct0_T &&v) = delete;

	struct0_T &operator=(const struct0_T &v)
	{
		for (int i = 0; i < 3; i++) {
			w[i] = v.w[i];
		}

		for (int i = 0; i < 6; i++) {
			r[i] = v.r[i];
			b[i] = v.b[i];
		}

		for (int i = 0; i < 16; i++) {
			K[i] = v.K[i];
			P[i] = v.P[i];
		}

		Mu_noise_var  = v.Mu_noise_var;
		Eta_noise_var = v.Eta_noise_var;
		dT            = v.dT;
		mk            = v.mk;
		Rho           = v.Rho;
	};

	struct0_T(const struct0_T &v)
	{
		*this = v;
	}

	struct0_T()
	{
		for (int i = 0; i < 3; i++) {
			w[i] = 0.0;
		}

		for (int i = 0; i < 6; i++) {
			r[i] = 0.0;
			b[i] = 0.0;
		}

		Mu_noise_var  = 0.0;
		Eta_noise_var = 0.0;
		dT            = 0.0;

		for (int i = 0; i < 16; i++) {
			K[i] = 0.0;
			P[i] = 0.0;
		}

		mk  = 0.0;
		Rho = 0.0;
	};
};

#endif /*typedef_struct0_T*/
#endif

/*
 * File trailer for get_quat_from_K_types.h
 *
 * [EOF]
 */
