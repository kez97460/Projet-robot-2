/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Fichier contenant les variables utilisées par plusieurs parties du programme du robot
 */

#ifndef EXTERN_H
#define	EXTERN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SPEED_MULTIPLIER 1.0 // speed constant multiplier to make speed unit ?? 
#define FORWARD_TIME_MULTIPLIER 10 // motorsCounter multiplier to make the distance unit ??
#define ROTATION_TIME_MULTIPLIER 10 // motorsCounter multiplier to make the angle unit "degrees"

extern volatile unsigned int motors_counter;
extern volatile unsigned int test_counter;
extern volatile unsigned char battery_value;

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

