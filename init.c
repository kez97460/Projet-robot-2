/* Projet robot 2 | Kézia Marcou - Lïam Lotte | 2023
 * Librairie init utilisée pour l'initialisation des fonctionnalités du robot
 * La fonction resetTimer0 se trouve actuellement ici, peut être modifié(interrupt ?)
 */

#include "init.h"
#include <stdio.h>

volatile int timer0_reset; // valeur de reset de timer0

volatile unsigned char use_survbat = 0;
volatile unsigned char use_interrupts = 0;
volatile unsigned char use_motors = 0;
volatile unsigned char use_timer0 = 0;
volatile unsigned char use_usart = 0;
volatile unsigned char use_i2c = 0;


// initialises Colck at Fosc = 8 MHz
void initClock()
{
    /* Clock (OSCCON register) : page 32 */
   OSCCONbits.IRCF0 = 1 ;
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;
}

// resets Timer0 to its starting value
void resetTimer0()
{
    TMR0H = (timer0_reset >> 8) & 0xFF;
    TMR0L = timer0_reset & 0xFF;
}

// Initialise Timer0 and set frequency to 100Hz
void initTimer0()
{
    /* Timer0 (T0CON register) : page 125 */
    T0CONbits.T0CS = 0; // runs on internal clock
    T0CONbits.T08BIT = 0; // 16 bit
    T0CONbits.TMR0ON = 1; // Turn timer0 on
    T0CONbits.PSA = 1; // prescaler off

    // Frequency settings
    // T0CONbits.T0PS = 0b0; // Prescaler to ...
    timer0_reset = 45535; // reset value (period adjustment)
    resetTimer0();

    use_timer0 = 1;
}

// initialise PWM for both motors, frequency is 1kHz
void initMotors()
{
    /* Timer2 (T2CON register) : page 135 */
    T2CONbits.TMR2ON = 1; // timer2 ON
    T2CONbits.T2CKPS = 0b10; // prescaler = 16
    PR2 = 124; // reset value -> precise period adjustment for 1kHz


    /* PWM (CCP module) : page 141 */
    CCP1CONbits.CCP1M = 0b1100; // PWM mode for motor 1
    CCPR1L = 0; // duty cycle 1 = 0
    CCP1CONbits.DC1B = 0;

    CCP2CONbits.CCP2M = 0b1100; // PWM mode for motor 2
    CCPR2L = 0; // duty cycle 2 = 0
    CCP2CONbits.DC2B = 0;

    /* Peripherals */
    TRISAbits.RA6 = 0; // RA6 = DIRD : output (Right motor direction)
    TRISAbits.RA7 = 0; // RA7 = DIRG : output (Left motor direction)

    TRISCbits.RC1 = 0; // RC1 = PWMD = CCP2 : output (Right motor PWM)
    TRISCbits.RC2 = 0; // RC2 = PWMG = CCP1 : output (Left motor PWM)

    use_motors = 1;
}

void initInterrupts()
{
    /* Interrupts : page 93 */
    // int0 : interrupt tï¿½lï¿½commande
    INTCON2bits.INTEDG0 = 0; // Front descendant
    INTCONbits.INT0IE = 1; // Int0 on

    // Timer0 interrupt
    INTCONbits.TMR0IE = 1; // timer0 interrupt on
    
    //general interrupts
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1; // enable interrupts globally

    use_interrupts = 1;
}

void initSurvBattery()
{
    /*
    ADCON1bits.VCFG=0; // inutile configuration par defaut
    //Choix TAD/
    ADCON2bits.ADCS=4;
    //T acquisition/
    ADCON2bits.ACQT=2;  // Temps acq = 6us > 4.2us
    // Choix AN2
    ADCON0bits.CHS=2;
    // Justification à droite
    ADCON2bits.ADFM = 1;
    // Validation ADC (demarage peripherique)
    ADCON0bits.ADON=1;
    //Configuration des voies analogiques et digitles
    ADCON1bits.PCFG=12;//AN0, AN1, AN2 analog, reste digital

    TRISAbits.RA2=1;
    TRISBbits.RB5=0;

    ADCON0bits.GO = 1; // Start a measure
    */

    ADCON1bits.VCFG0 = 0; // Vref+ = Vdd
    ADCON1bits.VCFG1 = 0; // Vref- = Vss
    ADCON1bits.PCFG = 0b1100; // Entrées AN0-AN2 en analog
    ADCON0bits.CHS = 0b0010; // Entrée de l'ADC : AN2
    ADCON2bits.ADCS = 0b100;
    ADCON2bits.ACQT = 0b010; // Temps acq = 6us > 4.2us
    ADCON2bits.ADFM = 1; // right justified
    ADCON0bits.ADON = 1; // ADC ON
    
    use_survbat = 1;
}

void initSerial()
{
    BAUDCONbits.BRG16 = 0; //permet de faire fonctionner le baud rate generator en 16bits
    TXSTAbits.BRGH = 1; //  On règle le high baud rate en mode high speed
    TXSTAbits.SYNC = 0; // on règle en mode asynchrone
    SPBRG = 51; // 9615 baud au lieu de 9600
    // TRISCbits.RC6 = 1; // mise de la pin en sortie TX, c'est par cette pin que ce fait la communication série
    TRISCbits.TRISC6 = 0; // ??? 
    RCSTAbits.SPEN = 1; // initialisation de SPEN, ce bit permet d'autoriser le port de communication série
    TXSTAbits.TXEN = 1; // initialisation de TXEN, ce bit permet d'autoriser la transmission

    PIR1bits.TXIF = 0;
    PIE1bits.TXIE = 0;
    RCSTAbits.CREN = 1; //enables receiver

    printf("UART initialised \r\n");

    use_usart = 1;
}

void initI2c()
{
    // SCL et SDA en entrée
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    // Validation I2C
    // SSPCON1bits.SSPEN = 1;
    // MSSP en mode maitre
    // SSPCON1bits.SSPM=8;
    // Control Slew Rate
    // SSPSTATbits.SMP = 1;
    // Vitesse 100kb/s
    // SSPADD = 9; // SSPADD = (Fosc/4*Baudrate)-1

    // Copied from MI2C.c
    SSPSTAT = 0x80; // Slew rate 100KHz
    SSPCON1 = 0x28; // Master Mode Enable, Sclock = FOSC/(4 * (SSPADD + 1)) I2C bus,
    SSPCON2 = 0x00;
    SSPADD = 0x13; // Prediviseur pour SCL = 100KHz a 8MHz

    use_i2c = 1;
}

// Full initialisation of the robot
/*char initRobotFull()
{
    // Capteurs IR off
}*/