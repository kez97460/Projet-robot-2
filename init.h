/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Librairie init utilisée pour l'initialisation des fonctionnalités du robot
 * La fonction resetTimer0 se trouve actuellement ici, peut être modifié (interrupt ?)
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f2520.h>
#include "MI2C.h"
#include "extern.h"


void resetTimer0();

void initClock();
void initTimer0();
void initPWM();
void initUSART();
void initInterrupts();
void initSurvBat();
char initRobotFull();



#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

