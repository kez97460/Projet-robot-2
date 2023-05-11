/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Fichier contenant les variables utilisées par plusieurs parties du programme du robot
 */

#ifndef EXTERN_H
#define	EXTERN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SPEED_MULTIPLIER 1.0 // speed constant multiplier

volatile int motors_counter; // counts time for the motors
volatile int test_counter; // counts time for ledtest, for testing

volatile int battery_value; // battery value as an 8 bit integer



#ifdef	__cplusplus
}
#endif

#endif	/* EXTERN_H */

