#ifndef FONCTIONNEMENT_H
#define	FONCTIONNEMENT_H

#include"p18f2520.h"
#include<stdio.h>
#include<stdlib.h>

void fonctionnement(void);
unsigned char mesurer_distance(void);
void LED_print(unsigned char data);
void blink(void);
void stop(void);
unsigned char etat_bat(void);

#endif	/* FONCTIONNEMENT_H */

