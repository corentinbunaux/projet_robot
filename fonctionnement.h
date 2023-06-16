#ifndef FONCTIONNEMENT_H
#define FONCTIONNEMENT_H

#include "p18f2520.h"
#include <stdio.h>
#include <stdlib.h>

void fonctionnement(void);
/*
fonction qui decrit les différents etats de fonctionnement du robot. Le robot est initialisé à l'état 0. Dans l'état 0 et 3, le robot tourne vers la gauche.
Dans l'état 1 et 4, il tourne vers la droite. Dans l'état 5, il avance tout droit. Les valeurs de RA6 et RA7 ne correspondent pas aux états décrits en raison
d'un mauvais fonctionnement de l'embase.
*/

unsigned char mesurer_distance(void);
/*
fonction permettant de mesurer la distance entre le robot et l'obstacle grâce aux capteurs IR. L'ADC est utilisé sur l'entrée analogique 1 et 0.
La valeur de la distance est la moyenne des deux mesures effectuées (permet de centrer le robot par rapport à l'obstacle.)
*/

void LED_print(unsigned char data);
/*
fonction permettant d'afficher la distance entre le robot et l'obstacle (en héxadécimal) sur le réseau de LEDs intégré à la carte.
*/

void blink(void);
/*
fonction de test, permettant de mesurer la période de l'horloge interne sur Proteus. Cette fonction n'est plus utilisée dans notre code mais
nous a permis de vérifer la valeur de l'horloge interne.
*/

void stop(void);
/*
fonction permettant d'arrêter le robot après son avancée. Les rapports cycliques des PMW sont mis à 0, tout comme les broches contrôlant le
sens des moteurs, et la LED d'activation du robot. Le robot est réinitialisé à l'état 0 sur la position qu'il occupe.
*/

unsigned char etat_bat(void);
/*
fonction permettant de mesurer l'état de la batterie à l'instant t. L'ADC est utilisé sur l'entrée analogique 2.
*/

#endif /* FONCTIONNEMENT_H */
