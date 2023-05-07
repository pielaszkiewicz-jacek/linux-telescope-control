/*
 * m_logic.h
 *
 *  Created on: 2010-10-29
 *      Author: Jacek Pielaszkiewicz
 */

#ifndef M_LOGIC_H_
#define M_LOGIC_H_

#include "FreeRTOS.h"
#include "m_logic_ramp.h"
#include "queue.h"
#include "task.h"

/*
 * Struktura kontrolna pojedynczej osi
 */

#define T_MOTOR_CONTROL_WORD_DUMY 0x00 //((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15))
#define T_MOTOR_CONTROL_WORD_MDA (1 << 11)
#define T_MOTOR_CONTROL_WORD_CA3 (1 << 10)
#define T_MOTOR_CONTROL_WORD_CA2 (1 << 9)
#define T_MOTOR_CONTROL_WORD_CA1 (1 << 8)
#define T_MOTOR_CONTROL_WORD_CA0 (1 << 7)
#define T_MOTOR_CONTROL_WORD_CA                                                                                        \
	(T_MOTOR_CONTROL_WORD_CA0 | T_MOTOR_CONTROL_WORD_CA1 | T_MOTOR_CONTROL_WORD_CA2 | T_MOTOR_CONTROL_WORD_CA3)
#define T_MOTOR_CONTROL_WORD_PHA (1 << 6)
#define T_MOTOR_CONTROL_WORD_MDB (1 << 5)
#define T_MOTOR_CONTROL_WORD_CB3 (1 << 4)
#define T_MOTOR_CONTROL_WORD_CB2 (1 << 3)
#define T_MOTOR_CONTROL_WORD_CB1 (1 << 2)
#define T_MOTOR_CONTROL_WORD_CB0 (1 << 1)
#define T_MOTOR_CONTROL_WORD_CB                                                                                        \
	(T_MOTOR_CONTROL_WORD_CB0 | T_MOTOR_CONTROL_WORD_CB1 | T_MOTOR_CONTROL_WORD_CB2 | T_MOTOR_CONTROL_WORD_CB3)
#define T_MOTOR_CONTROL_WORD_PHB (1 << 0)

#define T_MOTOR_CONTROL_SQUARE_1                                                                                       \
	(T_MOTOR_CONTROL_WORD_DUMY | T_MOTOR_CONTROL_WORD_PHB | T_MOTOR_CONTROL_WORD_MDA | T_MOTOR_CONTROL_WORD_MDB |      \
	 T_MOTOR_CONTROL_WORD_CA | T_MOTOR_CONTROL_WORD_CB)

#define T_MOTOR_CONTROL_SQUARE_2                                                                                       \
	(T_MOTOR_CONTROL_WORD_DUMY | T_MOTOR_CONTROL_WORD_PHA | T_MOTOR_CONTROL_WORD_PHB | T_MOTOR_CONTROL_WORD_MDA |      \
	 T_MOTOR_CONTROL_WORD_MDB | T_MOTOR_CONTROL_WORD_CA | T_MOTOR_CONTROL_WORD_CB)

#define T_MOTOR_CONTROL_SQUARE_3                                                                                       \
	(T_MOTOR_CONTROL_WORD_DUMY | T_MOTOR_CONTROL_WORD_PHA | T_MOTOR_CONTROL_WORD_MDA | T_MOTOR_CONTROL_WORD_MDB |      \
	 T_MOTOR_CONTROL_WORD_CA | T_MOTOR_CONTROL_WORD_CB)

#define T_MOTOR_CONTROL_SQUARE_4                                                                                       \
	(T_MOTOR_CONTROL_WORD_DUMY | T_MOTOR_CONTROL_WORD_MDA | T_MOTOR_CONTROL_WORD_MDB | T_MOTOR_CONTROL_WORD_CA |       \
	 T_MOTOR_CONTROL_WORD_CB)

#define T_MOTOR_DEFAULT_BASE_MOTOR_RESOLUTION 200           // Bazowa rozdzielczosc silnika krokowego
#define T_MOTOR_DEFAULT_MICROSTEPS T_VAL_DEFAULT_MICROSTEPS // Maklsymalna rozdzielczosc
#define T_MOTOR_DEFAULT_DAC_RESOLUTION T_VAL_DAC_RESOLUTION
#define T_MOTOR_DEFAULT_FREQUENCY 9999.0 // Czestotliwosc probkowania
#define T_MOTOR_DEFAULT_CALC_FREQUENCY 8
#define T_MOTOR_DEFAULT_SAFE_FACTOR 0.999

#define T_MOTOR_DEFAULT_STEP_ANGLE_SIZE_MIN 2
#define T_MOTOR_DEFAULT_STEP_ANGLE_SIZE_MAX 128

#define T_MOTOR_DIRECTION_NONE 0x00
#define T_MOTOR_DIRECTION_LEFT 0x01
#define T_MOTOR_DIRECTION_RIGHT 0x02

#define T_MOTOR_CONTROLER_STATUS_IDLE 0x00       // Kontroler aktualnie nie ma nic do robotu
#define T_MOTOR_CONTROLER_STATUS_BUSY_MOVE 0x01  // Kontroler aktualnie jest w trakcie wykonywania przemieszczenia
#define T_MOTOR_CONTROLER_STATUS_BUSY_SPEED 0x02 // Kontroler aktualnie przyspieszania lub biegu z zadana predkoscia
#define T_MOTOR_CONTROLER_STATUS_BUSY_STOP 0x03  // Kontroler aktualnie jest w trakcie hamowania

#define T_MOTOR_SYNCH_REQUESTS_COUNT 3

#define T_MOTOR_REQUESTS_COUNT 10
#define T_MOTOR_REQUEST_STATUS_FREE 0x00
#define T_MOTOR_REQUEST_STATUS_READY 0x01
#define T_MOTOR_REQUEST_STATUS_IN_USE 0x02

#define T_MOTOR_MOVE_REQUEST_TYPE_MOVE_DELTA 0x01
#define T_MOTOR_MOVE_REQUEST_TYPE_MOVE_POSITION 0x02
#define T_MOTOR_MOVE_REQUEST_TYPE_MOVE_POSITION_OPT 0x03
#define T_MOTOR_MOVE_REQUEST_TYPE_MOVE_SPEED 0x04
#define T_MOTOR_MOVE_REQUEST_TYPE_MOVE_STOP 0x05

#define T_MOTOR_TASK_STACK_DEPTH 512

/*
 * Strultura przechowuje parametery generacji mikrokrokow
 */
typedef struct TMotorMicrostepControl {
	uint16_t motorControlWordPrevious;
	uint16_t motorControlWord; // Rekord wysylany do sterownika urzadzenia. Wartosc slowa jest wysylana do
	                           // koncowki mocy sterownika silnika

	uint32_t msSeq; // Wartosc na podstawie ktorej bedzie liczony sinus oraz cosinus

	// Obie wartosci reprezentujaja maksymalna rozdzielczosc korku.
	// Wartosc ta ograniczona jest maksymalna rozdzielnczoscia przetwornika cyfrowo-analogowego
	uint32_t msSeqMaxValue;

	uint32_t inA; // Wartosc DAC dla A
	uint32_t inB; // Wartosc DAC dla B

	uint32_t inANext; // Wartosc DAC dla A
	uint32_t inBNext; // Wartosc DAC dla B

	uint8_t crossZero;

	// Aktualna pozycja kontrolera wynikajaca ze slowa
	uint32_t controlerPositionMaxValue; // Licznik nadrzedny pozycji - graniczna wartosc
	uint32_t controlerPosition;         // Licznik nadrzedny pozycji

	double controlerPositionMaxValueRadians; // Licznik nadrzedny pozycji - graniczna wartosc
	double controlerPositionRadians;         // Licznik nadrzedny pozycji

	uint8_t resetMasterRecord; // Zbacznik czy licznik nadrzedny ma byc resetowany po osiągnieci wartości granicznej

	// Zestaw wartosci pomocniczych okrelsalcych poszczegolne cwiartki sinusa oraz cosinusa
	uint32_t range_90;  // Wartosc odpowiadajaca kontowi 90 stopni
	uint32_t range_180; // Wartosc odpowiadajaca kontowi 180 stopni
	uint32_t range_270; // Wartosc odpowiadajaca kontowi 270 stopni

} TMotorMicrostepControl;

/*
 * Struktura przechowujue wymagane parametery pracy kontrolera
 */
typedef struct TMotorControlHardwareConfiguration {
	uint32_t requestTimeOut; // Czas oczekiwania na zwolnienie miejsca w kolejsce
	double   deceleration;   // Przyspieszenia hamowania dla requestow kontrolnych

	uint32_t maxSteps;
	uint32_t motorNativeResolution; // Natywna rozdzielczosc silnika

	uint32_t deviceMotorID; // ID uzadzenia silnika SPI
	uint32_t dacAId;        // ID DAC dla A
	uint32_t dacBId;        // ID DAC dla B

	uint8_t updateAllDacs; // Znacznik czy modyfikowane beda wszystkie DAC

	uint8_t  motorStateRead; // Flaga mowiaca czy status silnika bedzie czytany
	uint16_t motorState[10]; // Aktualny status kontrolera silnika

	uint8_t enebleControl; // Kontrolowanie enable. Aktualnie nie uzywane. PINY zawsze ustawione na 0.

} TMotorControlHardwareConfiguration;

/*
 * Struktura definiuje pojedyncze rzadanie wykonania przemieszczenia
 */
typedef struct TMotorControlInputRequest {
	uint8_t direction;   // Kierunek obrotu
	double  speed;       // Docelowa predkosc
	double  aceleration; // Przyspieszenie oraz hamowanie
	uint8_t movmentType; // Rodzaj przemieszczenia. Mozliwe trzy wartosci przesuniecie do zadanej pozycji, rozpedzenie
	                     // lub zwolnienie do zadanej predkosci oraz
	                     // zatrzymanie

	uint32_t distance;        // Droga do przebycia lub pozycja do osiagniecia w krokach
	double   distanceRadians; // Droga do przebycia lub pozycja do osiagniecia w krokach
	uint8_t  distanceInRadians;

	unsigned int stepAngle;
	unsigned int maxStepAngle;

} TMotorControlInputRequest;

typedef struct TSynchronizedMotorControlInputRequest {
	TMotorControlInputRequest requestData[3];
} TSynchronizedMotorControlInputRequest;

typedef struct TMotorControlRequestData {
	uint8_t direction;   // Kierunek obrotu
	double  speed;       // Docelowa predkosc
	double  aceleration; // Przyspieszenie oraz hamowanie
	uint8_t movmentType; // Rodzaj przemieszczenia. Mozliwe trzy wartosci przesuniecie do zadanej pozycji, rozpedzenie
	                     // lub zwolnienie do zadanej predkosci oraz
	                     // zatrzymanie

	uint32_t distance;        // Droga do przebycia
	double   distanceRadians; // Droga do przebycia w radianach
	uint8_t  distanceInRadians;

	unsigned int stepAngle;
	unsigned int maxStepAngle;

} TMotorControlRequestData;

typedef struct TSynchronizedMotorControlRequest {
	TMotorControlRequestData requestData[3];
	uint8_t                  setInfo[3];

} TSynchronizedMotorControlRequest;


typedef struct TMotorControlRequestsQueue {
	xQueueHandle queueHandle;

} TMotorControlRequestsQueue;

typedef struct TMotorControlTasks {
	xTaskHandle *monitorTaskHandle;
	xTaskHandle *requestsProcessingTaskHandle;
} TMotorControlTasks;

typedef struct TMotorControlRequests {
	// Lista requestow
	TMotorControlRequestsQueue requestsQueue;

	// Aktualnie przetwarzany request
	TMotorControlRequestData currentRequest;
	uint8_t                  isRequestPending;

	// Oznaczenie czy jest przetwarzany request kontrolny
	uint8_t isControlRequest;

} TMotorControlRequests;

/*
 * Struktura przechowuje liczniki kontrolera
 */
typedef struct TMotorControlCounters {
	uint32_t calculationFrequencyCounter; // Licznik jest caly czas inkrementowany
	// Po mosiagnieciu zadanej wartosci wyzwalna jest operacja wyliczenia kolejnego
	// przemieszczenia.
} TMotorControlCounters;

/*
 * Struktura przechowuje statusy pracy kontrolera
 *
 */
typedef struct TMotorControlStatuses {
	uint8_t actualStatus;    // Aktualny status kontrolera osi
	uint8_t actualDirection; // Aktualny kierunek obrotu

} TMotorControlStatuses;

typedef struct TMotorControl {
	uint8_t logicDeviceID;

	// Parametery generacji mikrokrokow oraz informacja o aktualnej pozycji kontrolera osi
	TMotorMicrostepControl microstepControl;

	// Zestaw parameterow na podstawie ktorych beda obliczane parametery rampy kontrolera
	TMotorRampInfo speedRampControl;

	// Konfiguracja kontrolera
	TMotorControlHardwareConfiguration controlerConfgiuration;

	// Liczniki kontrolne
	TMotorControlCounters controlCounters;

	// Statusy
	TMotorControlStatuses controlerStatuses;

	// Requesty
	TMotorControlRequests controlerRequests;

	// Taski kontrolera
	TMotorControlTasks controlerTasks;

} TMotorControl;


extern void    LOGIC_setControlerParameters(TMotorControl *, uint32_t, uint32_t, double, uint32_t, uint32_t, uint32_t,
                                            uint8_t);
extern uint8_t LOGIC_requestInsert(TMotorControl *, TMotorControlInputRequest *);
extern void    LOGIC_removeAllRequestsFromQueue(TMotorControl *);
extern void    LOGIC_mainIRQRadians(TMotorControl *);
extern void    LOGIC_setStepAngles(TMotorControl *);
extern void    LOGIC_init(TMotorControl *, uint8_t);
extern void    LOGIC_taskInitRadians(void);
extern void    LOGIC_stopStepsGeneration(TMotorControl *);
extern void    DEVICE_createAxisInfo(char *, uint32_t);
extern double  LOGIC_distanceToRadians(TMotorControl *, uint32_t);

#endif /* M_LOGIC_H_ */
