#include"p18f2520.h"
#include"IT.h"
#include"fonctionnement.h"
#include"init.h"
#include"MI2C.h"

#pragma code HighVector=0x08

unsigned float V_SEUIL = 2.5 ;

int etat = 0, temps_tourne =0, i, nombre_mes =0, temps_bat=0, compteur=0;
unsigned char distance;
unsigned int sum_mes, UBAT;
int tourne =1;
char Recv_Buff[3];

void IntHighVector(void)
{
    _asm
        goto HighISR
    _endasm
}
#pragma code

#pragma interrupt HighISR

void HighISR(void)
{
    if(INTCONbits.INT0IF){
        Lire_i2c_Telecom(0xA2, Recv_Buff);
        if(Recv_Buff[1] == 0x33){
            PORTBbits.RB5=1;
        }
        temps_tourne=0;
        etat=0;
        temps_bat=0;
        INTCONbits.INT0IF = 0;
    }

    if (INTCONbits.TMR0IF && PORTBbits.RB5 )
    {

        //blink(); //LED for timer
        temps_tourne++;
        temps_bat++;
        distance = mesurer_distance(); //distance between the robot and the obstacle
        LED_print(distance);
        printf("%x\r", distance);
        if (temps_tourne == 70 && etat!=5) //motors every 3.5s (=90*50*10-3)
        {
            etat++; //state of the robot
            printf("Etat %d\r",etat);
            if (etat== 4)
            {
                etat= 0;
            }
            temps_tourne = 0;
        }

        if(temps_bat == 20) //check_battery every 1s (50*10-3*20)
        {
            UBAT = (int)etat_bat();
            if(nombre_mes < 4)
            {
                nombre_mes++;
                sum_mes+= UBAT;
            }
            else
            {
                if(sum_mes/4 < (255/5)*V_SEUIL)
                {
                    printf("\r\rBatterie faible\r\r"); //avg tension of the battery
                    PORTBbits.RB5 = 0;
                }
                printf("Vbat_moyen = %d mV\r",(sum_mes/4)*19);
                sum_mes = 0;
                nombre_mes = 0;
            }

            temps_bat=0;
        }

        if(distance>0x12)
        {
            printf("avancer tout droit");
            etat = 5;
        }
        if(etat==5 && compteur == 68)
        {
            PORTBbits.RB5=0;
            compteur=0;
        }
        if(etat==5) compteur++;

        INTCONbits.TMR0IF = 0; //IT flag
    }
}