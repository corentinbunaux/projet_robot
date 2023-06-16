#include "p18f2520.h"
#include "IT.h"
#include "init.h"

void fonctionnement(void)
{

    if (etat == 0 || etat == 3) // états dans lesquels le robot doit tourner vers la gauche
    {
        CCPR1L = 50; // initilialisation du rapport cyclique
        CCPR2L = 50;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA6 = 0;
        PORTAbits.RA7 = 0; // choix du sens de rotation des moteurs (l'embase est dysfonctionnelle et le sens de rotation du moteur gauche est inversé)
    }

    else if (etat == 1 || etat == 2) // états dans lesquels le robot doit tourner vers la droite
    {
        CCPR1L = 50; // initialisation du rapport cyclique
        CCPR2L = 50;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA7 = 1;
        PORTAbits.RA6 = 1; // choix du sens de rotation des moteurs
    }

    else if (etat = 5)
    {                 // état dans lequel le robot doit avancer tout droit
        CCPR1L = 100; // initialisation du rapport cyclique
        CCPR2L = 100;

        CCP1CONbits.DC1B0 = 1;
        CCP1CONbits.DC1B1 = 0; // Lancement du rapport cyclique

        CCP2CONbits.DC2B0 = 1;
        CCP2CONbits.DC2B1 = 0;

        PORTAbits.RA7 = 1; // choix du sens de rotation des moteurs
        PORTAbits.RA6 = 0;
    }
}

unsigned char mesurer_distance(void)
{
    unsigned char dist_capt_D, dist_capt_G; // définition des variables contenant la distance entre chaque capteur et l'obstacle

    init_ADC_AN1(); // initialisation de l'ADC sur l'entrée analogique 1
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE) // attente de conversion
        ;
    dist_capt_G = ADRESH; // attribution de la valeur de distance à la variable

    init_ADC_AN0(); // initialisation de l'ADC sur l'entrée analogique 0
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE) // attente de conversion
        ;
    dist_capt_D = ADRESH; // attribution de la valeur de distance à la variable

    return (dist_capt_D + dist_capt_G) / 2; // distance retournée par la fonction vaut la moyenne des deux distances mesurées
}

void LED_print(unsigned char data)
{
    SSPSTATbits.SMP = 1; // contrôle de la vitesse de balayage désactivé pour le mode vitesse standard

    SSPCON2bits.SEN = 1; // début de condition sur SDA & SCL

    while (!PIR1bits.SSPIF)
        ; // attente de fin de transmition

    PIR1bits.SSPIF = 0; // transmition ok

    SSPBUF = 0x40; // Adresse en écriture

    while (!PIR1bits.SSPIF)
        ; // attente de l'envoi

    PIR1bits.SSPIF = 0; // envoi ok

    while (SSPCON2bits.ACKSTAT)
        ; // attente de réception de l'esclave

    SSPBUF = data; // envoi données

    while (!PIR1bits.SSPIF)
        ; // attente de l'envoi

    PIR1bits.SSPIF = 0; // envoi ok

    while (SSPCON2bits.ACKSTAT)
        ; // attente de réception de l'esclave

    SSPCON2bits.PEN = 1; // stop SDA & SCL

    while (!PIR1bits.SSPIF)
        ; // attente de l'envoi

    PIR1bits.SSPIF = 0; // envoi ok
}

void blink(void)
{
    PORTBbits.RB5 = ~PORTBbits.RB5; // changement d'état de la LED
    TMR0H = 0x3C;
    TMR0L = 0xAF;
}

unsigned char etat_bat(void)
{
    unsigned char UBAT; // définition de la variable de mesure de la batterie
    init_ADC_AN2();     // démarrage de l'ADC sur l'entrée analogique 2
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE) // attente de conversion
        ;
    UBAT = ADRESH; // attribution de la valeur de l'état de la batterie

    return UBAT; // retourne la valeur la batterie
}

void stop(void)
{
    CCPR1L = 0; // rapport cyclique des moteurs mis à 0
    CCPR2L = 0;

    CCP1CONbits.DC1B0 = 1; // Lancement du raopport cyclique
    CCP1CONbits.DC1B1 = 0;

    CCP2CONbits.DC2B0 = 1;
    CCP2CONbits.DC2B1 = 0;

    PORTAbits.RA6 = 0; // réinitialisation du sens de rotation des moteurs
    PORTAbits.RA7 = 0;

    PORTBbits.RB5 = 0; // arrêt du robot via la broche RB5 pour stopper les interruptions

    etat = 0; // réinitialisation de l'état du robot à l'état 0

    printf("Robot stop");
}
