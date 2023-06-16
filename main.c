#include"p18f2520.h"
#include"fonctionnement.h"
#include"init.h"
#include"IT.h"
#include<stdio.h>

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON



void main(void){
    init_all();
    while(1){
        if(PORTBbits.RB5) fonctionnement();
        else stop();
    }
}
