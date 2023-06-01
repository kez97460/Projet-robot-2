#include<p18f2520.h>
#include<stdio.h>

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

#define Adresse_U8 0x40
#define Adresse_Sonar 0xE0

void write_data(unsigned char adresse,unsigned char data);
unsigned int read_sonar(char adresse);

void write_data(unsigned char adresse,unsigned char data){

    SSPCON2bits.SEN = 1;  // Emission Start
    while (! PIR1bits.SSPIF ) ;  // Attente tant que SSPIF = 0
    PIR1bits.SSPIF = 0;
    SSPBUF = adresse;  // Emission de l'adresse
    while (! PIR1bits.SSPIF ) ;
    PIR1bits.SSPIF = 0;
    while ( SSPCON2bits.ACKSTAT );  // Test de ACK
    SSPBUF = data;   // Emission de la donnée
    while (! PIR1bits.SSPIF ) ;
    PIR1bits.SSPIF = 0;
    while ( SSPCON2bits.ACKSTAT );
    SSPCON2bits.PEN = 1;  // Emission STOP
    while (! PIR1bits.SSPIF ) ;  // Attente tant que SSPIF = 0
    PIR1bits.SSPIF = 0;
}
unsigned int read_sonar(char adresse){    /*Envoie Adresse*/
    char data;
    SSPCON2bits.SEN = 1;  // Emission Start
    while (!PIR1bits.SSPIF ) ;  // Attente tant que SSPIF = 0
    PIR1bits.SSPIF = 0;
    SSPBUF = adresse+1;  // Emission de l'adresse
    while (!PIR1bits.SSPIF ) ;
    PIR1bits.SSPIF = 0;
    while (SSPCON2bits.ACKSTAT );  // Test de ACK

    /*Reception*/
    SSPCON2bits.RCEN=1;// SSPBUF en reception
    while (!PIR1bits.SSPIF ) ; // Attente tant que SSPIF = 0
    PIR1bits.SSPIF = 0;
    data=SSPBUF;
    SSPCON2bits.ACKDT=1; // initiate NACK  pour fin de lecture
    SSPCON2bits.ACKEN=1;
    while(SSPCON2bits.ACKEN); // Attendre fin NACKEN
    PIR1bits.SSPIF = 0;
    SSPCON2bits.PEN=1; // send STOP condition
    while (!PIR1bits.SSPIF ) ;
    PIR1bits.SSPIF = 0;
    return data;
}
