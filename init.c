#include <stdio.h>
#include "p18f2520.h"
#include "MI2C.h"

void init_clock(void)
{
    /* L'horloge est initialisée à 8MHz */
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
}

void init_timer0(void)
{
    T0CONbits.TMR0ON = 1; // active le timer
    T0CONbits.T08BIT = 0; // le configure sur 16 bits
    T0CONbits.T0CS = 0;   // internal instruction cycle clock
    T0CONbits.T0PS2 = 0;  // prescaler à 2
    T0CONbits.T0PS1 = 0;  //
    T0CONbits.T0PS0 = 0;  //
    T0CONbits.PSA = 0;    // assignement du prescaler
    TMR0H = 0x3C;         // valeur du rechargement 15535
    TMR0L = 0xAF;
}

void init_timer2(void)
{
    /*
    prescaler à 4
    */
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;

    PR2 = 249; // valeur du pr2 le plus grand possible < 255

    /*
    rapport cyclique à 0 pour le moment
    */
    CCPR1L = 0;
    CCPR2L = 0;

    T2CONbits.TMR2ON = 1; // active le timer

    /*
    PWM mode
    */
    CCP1CONbits.DC1B0 = 0;
    CCP1CONbits.DC1B1 = 1;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 1;
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;
    CCP2CONbits.CCP2M3 = 1;
    CCP2CONbits.CCP2M2 = 1;
}

void init_ES(void)
{
    TRISBbits.RB0 = 1; // IT
    TRISBbits.RB5 = 0; // LED
    TRISCbits.RC3 = 1; // SCL en entree
    TRISCbits.RC4 = 1; // SDA en entree
    TRISCbits.RC1 = 0; // moteur droit en sortie
    TRISCbits.RC2 = 0; // moteur gauche en sortie
    TRISAbits.RA6 = 0; // RA6 en sortie
    TRISAbits.RA7 = 0; // RA7 en sortie
    TRISBbits.RB1 = 0; // RB1 en sortie
}

void init_ADC_AN2(void)
{
    /*
    ADCON1 configures the functions of the port pins.
    ADCON2 configures the A/D clock source, programmed acquisition time and justification.
    */

    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1; // initialise AN1 aet AN2 en sortie analogique (et AN0), les autres ports sont des sorties digitales.
                          //
    ADCON1bits.VCFG0 = 0; // tension de référence (VREF+ = VDD)
    ADCON1bits.VCFG1 = 0; // tensionde référence (VREF- = VSS)
                          //
    ADCON2bits.ADCS0 = 1; //
    ADCON2bits.ADCS1 = 0; //
    ADCON2bits.ADCS2 = 0; // configuration de la clock de conversion : Fosc/8
                          //
    ADCON2bits.ACQT0 = 1; //
    ADCON2bits.ACQT1 = 1; //
    ADCON2bits.ACQT2 = 0; // configuration du temps d'acquisition, TACQ=6TAD
                          //
    ADCON0bits.CHS0 = 0;  //
    ADCON0bits.CHS1 = 1;  //
    ADCON0bits.CHS2 = 0;  //
    ADCON0bits.CHS3 = 0;  // MUX sur AN2
                          //
    ADCON2bits.ADFM = 0;  // justifié à gauche
                          //
    ADCON0bits.ADON = 1;  // active l'adc
}

void init_ADC_AN1(void)
{
    /*
    ADCON1 configures the functions of the port pins.
    ADCON2 configures the A/D clock source, programmed acquisition time and justification.
    */

    ADCON1bits.PCFG0 = 0; //
    ADCON1bits.PCFG1 = 0; //
    ADCON1bits.PCFG2 = 1; //
    ADCON1bits.PCFG3 = 1; // initialise AN1 aet AN2 en sortie analogique (et AN0), les autres ports sont des sorties digitales.
                          //
    ADCON1bits.VCFG0 = 0; // VREF+ = VDD
    ADCON1bits.VCFG1 = 0; // VREF- = VSS
                          //
    ADCON2bits.ADCS0 = 1; //
    ADCON2bits.ADCS1 = 0; //
    ADCON2bits.ADCS2 = 0; // Fosc/8
                          //
    ADCON2bits.ACQT0 = 1; //
    ADCON2bits.ACQT1 = 1; //
    ADCON2bits.ACQT2 = 0; // TACQ=6TAD
                          //
    ADCON0bits.CHS0 = 1;  //
    ADCON0bits.CHS1 = 0;  //
    ADCON0bits.CHS2 = 0;  //
    ADCON0bits.CHS3 = 0;  // MUX sur AN1
                          //
    ADCON2bits.ADFM = 0;  // justifié à gauche
                          //
    ADCON0bits.ADON = 1;  // active l'adc
}
void init_ADC_AN0(void)
{
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;

    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;

    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS2 = 0;

    ADCON2bits.ACQT0 = 1;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT2 = 0;

    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;

    ADCON2bits.ADFM = 0;

    ADCON0bits.ADON = 1;
}

void init_UART(void)
{
    BAUDCONbits.BRG16 = 1; // the BRG operates in 16-bit mode
    TXSTAbits.SYNC = 0;    // horloge pas synchro entre les equipements
    TXSTAbits.BRGH = 1;    //
    SPBRGH = 0;            // UART of PIC18 impair
    SPBRG = 207;           // 9615bauds au lieu de 9600
                           //
    RCSTAbits.SPEN = 1;    //
    TXSTAbits.TXEN = 1;    // autorise d'afficher dans le terminal
}

void init_I2C(void)
{

    SSPCON1bits.SSPEN = 1; // validation i2c
                           //
    SSPCON1bits.SSPM3 = 1; // mode master
    SSPCON1bits.SSPM2 = 0; //
    SSPCON1bits.SSPM1 = 0; //
    SSPCON1bits.SSPM0 = 0; //
                           //
    SSPADD = 9;            // baud = 100 kb/s
}

void init_IT(void)
{
    INTCONbits.TMR0IE = 1;   // autorise les interruptions liées à l'overflow
    INTCON2bits.INTEDG1 = 1; // front montant
    INTCON2bits.INTEDG0 = 0; // front descendant
    INTCONbits.INT0IE = 1;   // autorise l'interruption int0
    INTCON3bits.INT1IE = 1;  // autorise l'interruption int1
    INTCONbits.PEIE = 1;     // autorise les its
    INTCONbits.GIE = 1;      // autorise les its
}

void init_all(void)
{
    init_clock();      // init horloge
    init_timer0();     // init timer 0
    init_timer2();     // init timer 2
    init_ES();         // entrées sorties
    init_UART();       // init UART
    MI2CInit();        // init I2C
    init_IT();         // init les it
    PORTBbits.RB5 = 0; // led on/off
    PORTBbits.RB1 = 0;
    printf("Initialisation OK\r");
}