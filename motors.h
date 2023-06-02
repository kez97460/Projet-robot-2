/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Code des moteurs du robot du cours de system design
 */
#ifndef MOTORS_H
#define	MOTORS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f2520.h>
#include "extern.h"
#include <stdio.h>

void motorsStop();
void motorsForward(int max_distance, int speed/*unit ?*/);
void motorsTurnLeft(int angle, int speed);
void motorsTurnRight(int angle, int speed);

void motorsTest(int speed, int timer, int dir_left, int dir_right);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTORS_H */

