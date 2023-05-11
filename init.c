/* Projet robot 2 | K�zia Marcou - L�am Lotte | 2023
 * Librairie init utilis�e pour l'initialisation des fonctionnalit�s du robot
 * La fonction resetTimer0 se trouve actuellement ici, peut �tre modifi� (interrupt ?)
 */

#include "init.h"

volatile int timer0_reset; // valeur de reset de timer0

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
}

// initialise PWM for both motors, frequency is 1kHz
void initPWM()
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
}

// initialise EUSART with baud rate = 9600bauds
void initUSART()
{
    /* USART : page 203 */
    // Baud rate
    BAUDCONbits.BRG16 = 1; // 16-bit baud rate -> activates SPBRGH
    TXSTAbits.SYNC = 0; // mode synchrone
    SPBRG = 103; // baud_rate = 9600 = Fosc/(4(n+1)) dans ces conditions (voir cours)

    // periph
    TRISCbits.RC6 = 1; // TX = RC6 en entr�e

    // interrupts
    PIR1bits.TXIF = 0; // force interrupt off

    // other
    RCSTAbits.SPEN = 1; // serial port enabled
    TXSTAbits.TXEN = 1; // transmission enabled
}

void initInterrupts()
{
    /* Interrupts : page 93 */
    // int0 : interrupt t�l�commande
    INTCON2bits.INTEDG0 = 0; // Front descendant
    INTCONbits.INT0IE = 1; // Int0 on

    // Timer0 interrupt
    INTCONbits.TMR0IE = 1; // timer0 interrupt on
    
    //general interrupts
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1; // enable interrupts globally
}

// Initialise the battery surveillance system
void initSurvBat()
{
    
}

// Full initialisation of the robot
char initRobotFull()
{
    // Capteurs IR off

}