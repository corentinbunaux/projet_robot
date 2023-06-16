#include "p18f2520.h"
#include "IT.h"
#include "init.h"

void fonctionnement(void)
{

    if (etat == 0 || etat == 3)
    {
        CCPR1L = 50;
        CCPR2L = 50;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA6 = 0;
        PORTAbits.RA7 = 0;
    }

    else if (etat == 1 || etat == 2)
    {
        CCPR1L = 50;
        CCPR2L = 50;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA7 = 1;
        PORTAbits.RA6 = 1;
    }

    else if (etat = 5){
        CCPR1L = 100;
        CCPR2L = 100;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA7 = 1;
        PORTAbits.RA6 = 0;
    }
}

unsigned char mesurer_distance(void)
{
    unsigned char dist_capt_D, dist_capt_G;

    init_ADC_AN1();
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE)
        ;
    dist_capt_G = ADRESH;

    init_ADC_AN0();
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE)
        ;
    dist_capt_D = ADRESH;
    return (dist_capt_D + dist_capt_G) / 2;
}

void LED_print(unsigned char data)
{
    SSPSTATbits.SMP = 1; // slew rate control disabled for standard speed mode

    SSPCON2bits.SEN = 1; // start condition on SDA & SCL pins

    while (!PIR1bits.SSPIF)
        ; // waiting for the end of the transmission

    PIR1bits.SSPIF = 0; // transmission ok

    SSPBUF = 0x40; // Adresse en �criture

    while (!PIR1bits.SSPIF)
        ; // waiting for send

    PIR1bits.SSPIF = 0; // send ok

    while (SSPCON2bits.ACKSTAT)
        ; // waiting for slave's reception

    SSPBUF = data; // send data

    while (!PIR1bits.SSPIF)
        ; // waiting for send

    PIR1bits.SSPIF = 0; // send ok

    while (SSPCON2bits.ACKSTAT)
        ; // waiting for slave's reception

    SSPCON2bits.PEN = 1; // stop SDA & SCL

    while (!PIR1bits.SSPIF)
        ; // waiting for send

    PIR1bits.SSPIF = 0; // send ok
}

void blink(void)
{
    PORTBbits.RB5 = ~PORTBbits.RB5;
    TMR0H = 0x3C;
    TMR0L = 0xAF;
}

unsigned char etat_bat(void)
{
    unsigned char UBAT;
    init_ADC_AN2();
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE)
        ;
    UBAT = ADRESH;

    return UBAT;
}

void stop(void)
{
    CCPR1L = 0;
    CCPR2L = 0;

    CCP1CONbits.DC1B0 = 1;
    CCP1CONbits.DC1B1 = 0;

    CCP2CONbits.DC2B0 = 1;
    CCP2CONbits.DC2B1 = 0;

    PORTAbits.RA6 = 0;
    PORTAbits.RA7 = 0;

    PORTBbits.RB5 = 0;
    etat=0;
    printf("Robot stop");
}
