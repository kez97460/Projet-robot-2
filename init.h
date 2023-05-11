/* Projet robot 2 | K�zia Marcou - L�am Lotte | 2023
 * Librairie init utilis�e pour l'initialisation des fonctionnalit�s du robot
 * La fonction resetTimer0 se trouve actuellement ici, peut �tre modifi� (interrupt ?)
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

