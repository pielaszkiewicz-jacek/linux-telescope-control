/*
 * m_logic_ramp_s.c
 *
 *  Created on: 2010-11-21
 *      Author: Jacek Pielaszkiewicz
 */

#ifndef _M_LOGIC_RAMP_S_H_
#define _M_LOGIC_RAMP_S_H_

#include "FreeRTOS.h"
#include <m_base.h>
#include <m_values.h>

#include <math.h>

#define T_MOTOR_PI T_VALUE_PI
#define T_MOTOR_2PI (2.0 * T_MOTOR_PI)

#define T_MOTOR_TRUE (T_M_TRUE)
#define T_MOTOR_FALSE (T_M_FALSE)

#define T_MOTOR_RAMP_MODE_NONE ((uint8_t) 0x00)
#define T_MOTOR_RAMP_MODE_MOVE ((uint8_t) 0x01)
#define T_MOTOR_RAMP_MODE_SPEED ((uint8_t) 0x02)
#define T_MOTOR_RAMP_MODE_STOP ((uint8_t) 0x03)

#define T_MOTOR_RAMP_PHASE_UKNOW ((uint8_t) 0x00)
#define T_MOTOR_RAMP_PHASE_A ((uint8_t) 0x01)
#define T_MOTOR_RAMP_PHASE_R ((uint8_t) 0x02)
#define T_MOTOR_RAMP_PHASE_D ((uint8_t) 0x03)

typedef struct TMotorRampInfo {
	//
	// 1. Czasy przejazdu
	//
	// - dla poszczegolnych faz
	double T1;
	double T1_PI;
	double T2;
	double T2_PI;
	double T3;
	double T3_PI;

	// - sumaryczne oraz przyrostowe
	double T1_Sum;
	double T2_Sum;
	double T3_Sum;

	// Czas uzywany dla przemieszczenia typu speed po rozpedzeniu/zachamowaniu do zadanej predkosci
	double SpeedTime;

	// Calkowity czas przejazdu
	double TSum;

	//
	// 2. Drogi przejazdu
	//
	// - sumaryczna
	double current;
	double delta;
	double S0;
	double S;

	// - dla poszczegolnych faz
	double L1;
	double L2;
	double L3;

	// Parametery przemieszczenia, maksymalna predkosc oraz przyspieszenie
	double Amax;
	double Vmax;

	double absoluteVmax;

	// Aktualna prekosc
	double V;

	// Pomocnicza inicalna prekosc uzywana dla wariantu prekosci
	double V0;

	//
	// 3. Parametery kontroli ruchu
	//
	// Tryb przemieszczenia
	uint8_t mode;
	uint8_t speedCalculation;

	// Rozmiar kontowy pojedynczego kroku
	double stepAngle;    // Rozmiar kontowy pojedynczego kroku
	double maxStepAngle; // Maksymalny rozmiar kontowy kroku

	unsigned int stepAngleMulti;    // Orginalny mnoznik przez ktory byl mnozony krok bazowy kontrolera
	unsigned int maxStepAngleMulti; // Orginalny mnoznik przez ktory byl mnozony krok bazowy kontrolera

	double controlerSteps;       // Odpowednik w liczbie krokow sterownika przemieszczenie
	                             // dla danego kwantu czasu
	uint32_t controlerStepsLong; // Liczba krokow kontrolera jako long

	uint32_t controlerStepsDiv;          // Liczba krokow kontrolera wykonywana podczas przemieszczenia
	                                     // Jest rowna controlerSteps / calculationFrequency
	uint32_t controlerStepsDivRest;      // Reszta z liczby krokow
	uint32_t controlerStepsDivRestDelta; // Reszta z liczby krokow

	uint8_t phase; // Faza ruchu

	double controlerStepsSum;

	double   frequency;            // Maksymalna czestotliwosc probkowania
	uint32_t nFrequency;           // Mnoznik okreslaljacy jak czesto bedzie wylkiczany kolejny krok
	double   calculationFrequency; // Czestotliwosc wyliczania kolejnych pozycji
	double   saveFactor;           // Wspolczynnik bespieczenstwa. Maksymalna wartosc to 1.0. Zabespiecza przed
	// sytuacja ze maksymalne obliczone przemieszczenie bedzie wieksze niz (maxStepAngle * nFrequency)

	double deltaT; // Przyrost czasu
	double rest;
	double t; // Aktualny czas

	// Zmienne sluzace sterowaniu czasoem
	long int tIndexMax;
	long int tIndex;

} TMotorRampInfo;

#define LOGIC_RAMP_TYPE_S 0x01
#define LOGIC_RAMP_TYPE_CONST 0x02

//
// Zestaw pomocniczych deklaracji
//
extern void     LOGIC_SRAMP_setStepAngle(TMotorRampInfo *, double, unsigned int, unsigned int); // ++
extern uint8_t  LOGIC_SRAMP_init(TMotorRampInfo *, double, double, double, uint8_t);
extern void     LOGIC_SRAMP_setFrequency(TMotorRampInfo *, double, uint32_t, double);
extern void     LOIGIC_SRAMP_setSpeedCalculation(TMotorRampInfo *, uint8_t);
extern uint32_t LOGIC_SRAMP_getSteps(TMotorRampInfo *, uint32_t);
extern void     LOGIC_SRAMP_globalInit(TMotorRampInfo *);
extern uint8_t  LOGIC_SRAMP_process(TMotorRampInfo *);
extern void     LOGIC_SRAMP_start(TMotorRampInfo *);

extern void     LOGIC_CONST_RAMP_setStepAngle(TMotorRampInfo *, double, unsigned int, unsigned int);
extern uint8_t  LOGIC_CONST_RAMP_init(TMotorRampInfo *, double, double, double, uint8_t);
extern void     LOGIC_CONST_RAMP_setFrequency(TMotorRampInfo *, double, uint32_t, double);
extern void     LOIGIC_CONST_RAMP_setSpeedCalculation(TMotorRampInfo *, uint8_t);
extern uint32_t LOGIC_CONST_RAMP_getSteps(TMotorRampInfo *, uint32_t);
extern void     LOGIC_CONST_RAMP_globalInit(TMotorRampInfo *);
extern uint8_t  LOGIC_CONST_RAMP_process(TMotorRampInfo *);
extern void     LOGIC_CONST_RAMP_start(TMotorRampInfo *);

//
// Zestaw glownych deklaracji
//
extern void     LOGIC_RAMP_setStepAngle(TMotorRampInfo *, double, unsigned int, unsigned int);
extern uint8_t  LOGIC_RAMP_init(TMotorRampInfo *, double, double, double, uint8_t);
extern void     LOGIC_RAMP_setFrequency(TMotorRampInfo *, double, uint32_t, double);
extern void     LOIGIC_RAMP_setSpeedCalculation(TMotorRampInfo *, uint8_t);
extern uint32_t LOGIC_RAMP_getSteps(TMotorRampInfo *, uint32_t);
extern void     LOGIC_RAMP_globalInit(TMotorRampInfo *);
extern uint8_t  LOGIC_RAMP_process(TMotorRampInfo *);
extern void     LOGIC_RAMP_start(TMotorRampInfo *);
extern void     LOGIC_RAMP_setType(uint8_t);
extern uint8_t  LOGIC_RAMP_getType(void);

#endif
