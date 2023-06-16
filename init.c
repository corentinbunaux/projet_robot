#include<stdio.h>
#include"p18f2520.h"
#include"MI2C.h"

void init_clock(void){
   OSCCONbits.IRCF0 = 1 ;
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;   //8MHz
}

void init_timer0(void){
   T0CONbits.TMR0ON = 1;    //enables timer
   T0CONbits.T08BIT = 0;    // 16 bits
   T0CONbits.T0CS = 0; //internal instruction cycle clock
   T0CONbits.T0PS2 = 0;
   T0CONbits.T0PS1 = 0;
   T0CONbits.T0PS0 = 0;
   T0CONbits.PSA = 0; //prescaler is assigned
   TMR0H = 0x3C;
   TMR0L = 0xAF;       //prescaler value
}

void init_timer2(void){
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0; //prescaler=4
    PR2 = 249;//p�riode du PWM
    CCPR1L = 0;
    CCPR2L = 0;
    T2CONbits.TMR2ON = 1;	//enables timer
    CCP1CONbits.DC1B0 = 0;
    CCP1CONbits.DC1B1 = 1;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 1;
    PORTAbits.RA6=1;
    PORTAbits.RA7=1;
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1; // mode pwm
    CCP2CONbits.CCP2M3 = 1;
    CCP2CONbits.CCP2M2 = 1;
}

void init_ES(void){
    TRISBbits.RB0 = 1; //IT 
    TRISBbits.RB5 = 0; //LED
    TRISCbits.RC3 = 1; //SCL en entr�e
    TRISCbits.RC4 = 1; //SDA en entr�e
    TRISCbits.RC1 =0; //right motor as an output
    TRISCbits.RC2 =0; //left motor as an output
    TRISAbits.RA6 = 0; //direction of right motor
    TRISAbits.RA7 = 0; //direction of left motor
    TRISBbits.RB1=0;
}

void init_ADC_AN2(void){
    //ADCON1 configures the functions of the port pins.
    //ADCON2 configures the A/D clock source, programmed acquisition time and justification.
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1; //set AN2 & AN1 as analog entries (AN0 too), others ports are set as digital entries.

    ADCON1bits.VCFG0 = 0; //Voltage Reference Configuration bit (VREF+ = VDD)
    ADCON1bits.VCFG1 = 0; //Voltage Reference Configuration bit (VREF- = VSS)

    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS2 = 0; //A/D Conversion clock selected bits, Fosc/8

    ADCON2bits.ACQT0 = 1;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT2 = 0; //A/D acquisition time selected bits, TACQ=6TAD

    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0; //MUX set on AN2

    ADCON2bits.ADFM = 0; //Result format selected bit left justified

    ADCON0bits.ADON = 1; //converter is enabled
}

void init_ADC_AN1(void){
    //ADCON1 configures the functions of the port pins.
    //ADCON2 configures the A/D clock source, programmed acquisition time and justification.

	ADCON1bits.PCFG0 = 0;
	ADCON1bits.PCFG1 = 0;
	ADCON1bits.PCFG2 = 1;
	ADCON1bits.PCFG3 = 1; //set AN2 & AN1 as analog entries (AN0 too), others ports are set as digital entries.

	ADCON1bits.VCFG0 = 0; //Voltage Reference Configuration bit (VREF+ = VDD)
	ADCON1bits.VCFG1 = 0; //Voltage Reference Configuration bit (VREF- = VSS)

	ADCON2bits.ADCS0 = 1;
	ADCON2bits.ADCS1 = 0;
	ADCON2bits.ADCS2 = 0; //A/D Conversion clock selected bits, Fosc/8

	ADCON2bits.ACQT0 = 1;
	ADCON2bits.ACQT1 = 1;
	ADCON2bits.ACQT2 = 0; //A/D acquisition time selected bits, TACQ=6TAD

	ADCON0bits.CHS0 = 1;
	ADCON0bits.CHS1 = 0;
	ADCON0bits.CHS2 = 0;
	ADCON0bits.CHS3 = 0; //MUX set on AN1

	ADCON2bits.ADFM = 0; //Result format selected bit left justified

	ADCON0bits.ADON = 1; //converter is enabled
}
void init_ADC_AN0(void){
    //ADCON1 configures the functions of the port pins.
    //ADCON2 configures the A/D clock source, programmed acquisition time and justification.

	ADCON1bits.PCFG0 = 0;
	ADCON1bits.PCFG1 = 0;
	ADCON1bits.PCFG2 = 1;
	ADCON1bits.PCFG3 = 1; //set AN2 & AN1 as analog entries (AN0 too), others ports are set as digital entries.

	ADCON1bits.VCFG0 = 0; //Voltage Reference Configuration bit (VREF+ = VDD)
	ADCON1bits.VCFG1 = 0; //Voltage Reference Configuration bit (VREF- = VSS)

	ADCON2bits.ADCS0 = 1;
	ADCON2bits.ADCS1 = 0;
	ADCON2bits.ADCS2 = 0; //A/D Conversion clock selected bits, Fosc/8

	ADCON2bits.ACQT0 = 1;
	ADCON2bits.ACQT1 = 1;
	ADCON2bits.ACQT2 = 0; //A/D acquisition time selected bits, TACQ=6TAD

	ADCON0bits.CHS0 = 0;
	ADCON0bits.CHS1 = 0;
	ADCON0bits.CHS2 = 0;
	ADCON0bits.CHS3 = 0; //MUX set on AN0

	ADCON2bits.ADFM = 0; //Result format selected bit left justified

	ADCON0bits.ADON = 1; //converter is enabled
}

void init_UART(void){
	BAUDCONbits.BRG16 = 1; //the BRG operates in 16-bit mode
	TXSTAbits.SYNC = 0; //clock not synchronized between equipements
        TXSTAbits.BRGH = 1;
        SPBRGH = 0; //UART of PIC18 impair
        SPBRG = 207; // 9615bauds instead of 9600bauds

	RCSTAbits.SPEN = 1;
	TXSTAbits.TXEN = 1; //allows printing in the terminal
}

void init_I2C(void){

    SSPCON1bits.SSPEN = 1; //validation i2c

    SSPCON1bits.SSPM3 = 1; // master mode
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;

    SSPADD = 9;             // baud = 100 kb/s
}

void init_IT(void){
   INTCONbits.TMR0IE = 1; //enables the overflow interrupt
	INTCON2bits.INTEDG1=1;	
	INTCON2bits.INTEDG0 = 0;
	INTCONbits.INT0IE = 1;
	INTCON3bits.INT1IE = 1;
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;


}

void init_all(void)
{
    init_clock();
    init_timer0();
    init_timer2();
    init_ES();
    init_UART();
    MI2CInit();
    init_IT();
    PORTBbits.RB5 = 0;
    PORTBbits.RB1=0;
    printf( "Initialisation OK\r");

}