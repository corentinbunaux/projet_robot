#ifndef INIT_TEST_H
#define	INIT_TEST_H

#include"p18f2520.h"
#include<string.h>

void init_clock(void);
void init_timer0(void);
void init_timer2(void);
void init_ES(void);
void init_ADC_AN2(void);
void init_ADC_AN1(void);
void init_ADC_AN0(void);
void init_UART(void);
void init_I2C(void);
void init_IT(void);
void init_all(void);

#endif





