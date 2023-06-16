#ifndef INIT_TEST_H
#define INIT_TEST_H

#include "p18f2520.h"
#include <string.h>

/*
initialise l'horloge interne à 8Mhz
*/
void init_clock(void);

/*
initialise le timer 0 à 50 ms
*/
void init_timer0(void);

/*
initialise le timer 2 pour générer des pwm et controler les moteurs
*/
void init_timer2(void);

/*
initalise les entrees sorties de la carte
*/
void init_ES(void);

/*
initalise l'adc sur la sortie AN2 pour la batterie
*/
void init_ADC_AN2(void);

/*
initalise l'adc sur la sortie AN1 pour les capteurs ir
*/
void init_ADC_AN1(void);

/*
initalise l'adc sur la sortie AN0 pour les capteurs ir
*/
void init_ADC_AN0(void);

/*
initalise l'uart à 9600 bd
*/
void init_UART(void);

/*
initialise l'i2c
*/
void init_I2C(void);

/*
initalise les interruptions
*/
void init_IT(void);

/*
initialise tous les periphs dont on a besoin
*/
void init_all(void);

#endif
