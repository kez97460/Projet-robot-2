/* Projet robot 2 | K�zia Marcou - L�am Lotte | 2023
 * Fichier contenant les variables utilis�es par plusieurs parties du programme du robot
 */

#ifndef EXTERN_H
#define	EXTERN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SPEED_MULTIPLIER 1.0 // speed constant multiplier to make speed unit ?? 
#define FORWARD_TIME_MULTIPLIER 120 // motorsCounter multiplier to make the distance unit ??
#define ROTATION_TIME_MULTIPLIER 56 // motorsCounter multiplier to make the angle unit "degrees"

#define DC_ONE_PERCENT 5

#define BATTERY_VALUE_LIMIT 639

#define SONAR_DISTANCE_MULTIPLIER 1
#define MAX_DISTANCE_OBSTACLE 40
#define NB_CONSECUTIVE_MEASURES 3

// For waitUntilSonarMeasure in main.c
#define MIN -1
#define MAX 1

extern volatile unsigned int motors_counter;
extern volatile unsigned int test_counter;
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

