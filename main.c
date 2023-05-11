/* Projet robot 2 | K�zia Marcou - L�am Lotte | 2023
 * Code principal du robot du cours de system design
 */

#include <p18f2520.h>
#include "MI2C.h"
#include "init.h"
#include "extern.h"


#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

void HighISR(void);

volatile short start; // is the program started ?

volatile int sonar_counter; // counts time for the sonar

extern volatile int motors_counter; // counts time for the motors. Can be modified by motors.c and main.c 

volatile int battery_measures_done; // counts time for battery measurements
volatile int battery_measures[4]; // stores measurements
extern volatile int battery_value; // mean of all 4 measurements, accessed by motor.c, modified by main.c

// Interrupt
#pragma code HighVector=0x08 // On va au vecteur d'interruption
void IntHighVector(void)
{
    /* Pas assez de place pour �crire du code -> on redirige vers une autre fct */
    _asm goto HighISR _endasm
}
#pragma code

#pragma interrupt HighISR
// Interrupt redirects here
void HighISR(void)
{
    // Remote control button pressed
    if(INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0; // flag off
        start = 1;
    }

    // Timer0 interrupt : every 10ms
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0; // flag off
        resetTimer0();

        // Test counter
        if(test_counter)
        {
            test_counter--;
        }

        // Motor counter (time until stop)
        if(motors_counter)
        {
            motors_counter--;
        }

        // Battery measurements
        if(battery_measures_done == 4)
        {
            battery_value = (battery_measures[0] + battery_measures[1] + battery_measures[2] + battery_measures[3]) / 4;
            battery_measures_done = 0;
            /* SEND MEASUREMENT USING USART */
            /* TURN ON/OFF LEDTEST */
        }
        else
        {
            /* MEASURE BATTERY LEVEL -> put value in battery_measures[battery_measures_done] */
            battery_measures_done++;
        }

        // Sonar counter
        if(sonar_counter)
        {
            sonar_counter--;
        }
        else
        {
            /* READ SONAR; */
            /* TRIG SONAR; */
            sonar_counter = 7; // sonar returns a value every ~70ms
        }
    }
}

int main()
{
    /* Inits and setup */
    initClock();
    initTimer0();
    initInterrupts();

    TRISBbits.RB5 = 0; // LedTest en sortie

    /* Infinite loop */
    while(420)
    {
        if(!test_counter)
        {
            PORTBbits.RB5 = ~PORTBbits.RB5;
            test_counter = 100; // 1s
        }
    }


}