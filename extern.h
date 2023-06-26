/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Fichier contenant les variables utilisées par plusieurs parties du programme du robot
 */

#ifndef EXTERN_H
#define	EXTERN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SPEED_MULTIPLIER 1.0 // speed constant multiplier
#define FORWARD_TIME_MULTIPLIER 120 // motorsCounter multiplier to make the distance unit cm
#define ROTATION_TIME_MULTIPLIER 31 // motorsCounter multiplier to make the angle unit "degrees"

#define DC_ONE_PERCENT 5

#define BATTERY_VALUE_LIMIT 639 // battery value equivalent to 10V

#define SONAR_DISTANCE_MULTIPLIER 1
#define MAX_DISTANCE_OBSTACLE 40
#define NB_CONSECUTIVE_MEASURES 3 // nb of measures needed to do anything

// For waitUntilSonarMeasure in main.c
#define MIN -1
#define MAX 1

extern volatile unsigned long motors_counter;
extern volatile unsigned long test_counter;
extern volatile unsigned int battery_value;

extern volatile unsigned char use_survbat;
extern volatile unsigned char use_interrupts;
extern volatile unsigned char use_motors;
extern volatile unsigned char use_timer0;
extern volatile unsigned char use_usart;
extern volatile unsigned char use_i2c;



#ifdef	__cplusplus
}
#endif

#endif	/* EXTERN_H */

