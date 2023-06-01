/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Code principal du robot du cours de system design
 */

#include <p18f2520.h>
#include <stdio.h>
#include "MI2C.h"
#include "init.h"
#include "extern.h"
#include "motors.h"


#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

volatile short start; // is the program started ?

volatile unsigned int sonar_counter; // counts time for the sonar
volatile unsigned int test_counter = 0; // counts time for ledtest, for testing. From extern.h
volatile unsigned int sleep_counter = 0;

volatile unsigned int motors_counter = 0; // counts time for the motors. From extern.h

volatile unsigned char battery_measures_done; // counts time for battery measurements
volatile unsigned char battery_measures[4]; // stores measurements
volatile unsigned char battery_value = 127; // mean of 4 battery measurements. From extern.h
volatile unsigned char UBAT; // single battery measurement

volatile char* uart_message;

void HighISR(void);
void sleep(float time_s);

// Interrupt
#pragma code HighVector=0x08 // On va au vecteur d'interruption
void IntHighVector(void)
{
    /* Pas assez de place pour écrire du code -> on redirige vers une autre fct */
    _asm goto HighISR _endasm
}
#pragma code

#pragma interrupt HighISR
// Interrupt redirects here
void HighISR(void)
{
    // Serial interrupt
    if(PIR1bits.TXIF)
    {
        if(uart_message == '\0')
        {
            PIE1bits.TXIE = 0; // fin de message : on désactive l'interrupt
        }
        else
        {
            TXREG = *uart_message;
            uart_message++;
        }
    }
    // End of serial interrupt

    // Remote control button pressed
    if(INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0; // flag off
        start = 1;
    }
    // End of Int0
    
    // Timer0 interrupt : every 10ms
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0; // flag off
        resetTimer0();

        // Test counter
        if(test_counter)
            test_counter--;

        // Sleep counter for the sleep function
        if(sleep_counter)
            sleep_counter--;

        // Motor counter (time until stop)
        if(motors_counter)
            motors_counter--;
        else
            motorsStop();

        // Battery measurements and surveillance
        if(use_survbat)
        {
            if(battery_measures_done == 4)
            {
                battery_value = (battery_measures[0] + battery_measures[1] + battery_measures[2] + battery_measures[3]) / 4;
                battery_measures_done = 0;
                printf("Battery level : %d \n", battery_value);
                // Turn led off if battery under 10V
                if(battery_value < 159)
                    PORTBbits.RB5 = 1;
                else
                    PORTBbits.RB5 = 0;
            }
            else
            {
                if(ADCON0bits.DONE)
                {
                    UBAT = 256 * ADRESH + ADRESL; // read the ADC acquisition
                    ADCON0bits.GO = 1; // restart acquisition
                    battery_measures[battery_measures_done] = UBAT;
                    battery_measures_done++;
                }
            }
        }
        
        // Sonar counter
        if(sonar_counter)
            sonar_counter--;
        else
        {
            /* READ SONAR; */
            /* TRIG SONAR; */
            sonar_counter = 7; // sonar returns a value every ~70ms
        }
    } 
    // End of Timer0 interrupt
}

#pragma code

void main(void)
{
    /* Inits and setup */
    initClock();
    initTimer0();
    initInterrupts();
    initMotors();
    initSurvBattery();
    initSerial();

    sleep(1);

    // Test serial (ne fonctionne pas)
    printf("Feur");
    PORTBbits.RB5 = 1;
    
    /* Tests moteurs
    motorsTest(50, 500, 1, 1); // speed, time(10*ms), dir_left, dir_right
    while(motors_counter);
    motorsTest(50, 500, 0, 0); // speed, time(10*ms), dir_left, dir_right
    */

    /* Infinite loop */
    while("Feur")
    {

    }


}

void sleep(float time_s)
{
    sleep_counter = 100 * time_s;
    while(sleep_counter);
}