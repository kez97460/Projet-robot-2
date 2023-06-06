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

volatile short start = 0; // is the program started ?

// volatile unsigned int sonar_counter = 0; // counts time for the sonar
volatile unsigned int test_counter = 0; // counts time for ledtest, for testing. From extern.h
volatile unsigned int sleep_counter = 0;
volatile unsigned int survbat_counter = 0;

volatile unsigned int motors_counter = 0; // counts time for the motors. From extern.h

// volatile unsigned int distance_sonar = 0;
// volatile unsigned int safety_sonar = 0;

volatile unsigned int battery_measures_done = 0; // counts time for battery measurements
volatile unsigned int battery_measures[4]; // stores measurements
volatile unsigned int battery_value = 0; // mean of 4 battery measurements. From extern.h
volatile unsigned int UBAT = 0; // single battery measurement

void HighISR(void);
void sleep(float time_s);
unsigned int sonarMeasure();
unsigned int survBattery();

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
    // Remote control button pressed
    if(INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0; // flag off
        start++;
        Write_PCF8574(0x40, 0); // ALL leds on
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
        if(use_survbat && !survbat_counter)
        {
            survbat_counter = 25 ; // mesure toutes les 250ms
            if(battery_measures_done == 4)
            {
                battery_value = (battery_measures[0] + battery_measures[1] + battery_measures[2] + battery_measures[3]) / 4;
                battery_measures_done = 0;
                // printf("Battery level : %d \n", battery_value);
                // Turn led off if battery under 10V
                if(battery_value < BATTERY_VALUE_LIMIT)
                    PORTBbits.RB5 = 1;
                else
                    PORTBbits.RB5 = 0;
            }
            else
            {
                battery_measures[battery_measures_done] = survBattery();
                battery_measures_done++;
            }
        }
        else if(use_survbat)
            survbat_counter--;
        
        // Sonar counter : measures could also be in main for our use case. IN MAIN
        /*
        if(sonar_counter)
            sonar_counter--;
        else
        {
            distance_sonar = SONAR_Read(0xE0,0x02); // 1ere mesure fausse !!!
            // printf("Distance : %d \r\n", distance); // debug print
            SONAR_Write(0xE0,0x00);
            SONAR_Write(0xE0,0x51);

            sonar_counter = 8; // sonar returns a value every ~80ms
        }
        */
    } 
    // End of Timer0 interrupt
}

#pragma code

void main(void)
{
    /* Inits and setup */
    int safety_sonar;
    int distance;
    int why;

    sleep_counter = 0;
    survbat_counter = 0;
    battery_measures_done = 0;

    initClock();
    initTimer0();
    initMotors();
    initSurvBattery();
    initSerial();
    initI2c();

    initInterrupts(); // Always last

    start = 0;
    while(!start); // wait for remote control

    if(use_usart)
        printf("Battery level : %d \r\n", battery_value); // Can't hurt to know

    // Tests moteurs
    /*
    motorsTest(20, 500, 1, 1); // pwm(%), time(10*ms), dir_left, dir_right
    while(motors_counter);
    motorsTest(20, 500, 0, 0); // pwm(%), time(10*ms), dir_left, dir_right
    while(motors_counter);
    */

    // Test leds
    // Write_PCF8574(0x40, 0b01010111); // 1 : off and 0 : on (for all 8 leds).

    // Calibration
    // motorsForward(100, 30);
    // while(motors_counter); // On attend la fin du déplacement
    // sleep(2);

    // motorsTurnRight(90, 20); // Calibration needed for ~90°
    //while(motors_counter); // On attend la fin du déplacement
    //sleep(0.5);

    //motorsTurnRight(90, 20); // Calibration needed for ~90°
    //while(motors_counter); // On attend la fin du déplacement
    //sleep(2);

    // motorsForward(100, 30);
    // while(motors_counter); // On attend la fin du déplacement
    // sleep(0.5);

    // Actual used code

    // Wait for no obstacle(1.5m)
    safety_sonar = NB_CONSECUTIVE_MEASURES;
    while(safety_sonar)
    {
        distance = sonarMeasure();
        if(distance > 150)
            safety_sonar--;
        else
            safety_sonar = NB_CONSECUTIVE_MEASURES;
        if(use_usart)
            printf("Measure : %d, target : MIN 150 \r\n", distance);
    }

    motorsForward(9999, 30); // Go forward for a very long amount of time

    safety_sonar = NB_CONSECUTIVE_MEASURES; // nb of consecutive measures needed to stop
    while(motors_counter && safety_sonar)
    {
        distance = sonarMeasure();
        why = 40;
        if(distance <= why)
            safety_sonar--;
            if(use_usart) // Debug print
                printf("Measure : %d, target : MAX %d , DECREASING SAFETY COUNTER \r\n", distance, why);
        else
        {
            safety_sonar = NB_CONSECUTIVE_MEASURES;
            if(use_usart) // Debug print
                printf("Measure : %d, target : MAX %d \r\n", distance, why);
        }
    }
    if(use_usart)
        printf("Stopping motors \r\n");
    motorsStop();
    sleep(0.5);

    motorsTurnRight(90, 20); // Calibration needed for ~90°
    while(motors_counter); // On attend la fin du déplacement
    sleep(0.5);

    motorsForward(100, 30); // Calibration needed for ~1m
    while(motors_counter); // On attend la fin du déplacement
    sleep(0.5);
    printf("Routine finished, going into loop \r\n");
    /* Infinite loop */
    while("Feur")
    {
        //Test sonar répété toutes les secondes
        sleep(1);
        if(use_usart)
        {
            printf("Distance : %d \r\n", sonarMeasure());
            printf("Battery value : %d \r\n", battery_value);
        }
    }
}

/* Functions */

void sleep(float time_s)
{
    sleep_counter = 100 * time_s;
    while(sleep_counter);
}

unsigned int sonarMeasure()
{
    unsigned int distance;
    SONAR_Write(0xE0,0x00);
    SONAR_Write(0xE0,0x51);
    sleep(0.080); // Attente pour le write >72ms
    distance = SONAR_Read(0xE0,0x02);
    distance = (unsigned int) distance * SONAR_DISTANCE_MULTIPLIER;
    return distance;
}

unsigned int survBattery()
{
    unsigned int UBAT;

    // ADCON0bits.ADON = 1; //start the ADC

    ADCON0bits.GO = 1; // start acquisition
    while ( !ADCON0bits.DONE ); // wait that the acquisition is finished
    UBAT = 256 * ADRESH + ADRESL; //read the ADC acquisition

    // ADCON0bits.ADON = 0; //stop the ADC

    return UBAT;
}