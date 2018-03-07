/*
 * File:   comm.c
 * Author: Marlon
 *
 * Created on October 8, 2017, 3:40 PM
 */


#include <xc.h>
#include "comm.h"

void delay_sec()  {
    T0CON=0x87;
    TMR0=18388; 
    INTCONbits.TMR0IF=0;
    while (INTCONbits.TMR0IF==0){
        while(!INTCONbits.TMR0IF){
            if(ADCON0bits.GODONE==0){ 
            ADCON0bits.GODONE = 1;
            }
        }
    }
}

 
unsigned int hex2bcd(unsigned char x){
    unsigned int y;
    
    y = (x / 100) << 8;
    y = ((x % 100)/10 << 4) | y;
    y = ((x % 100) % 10) | y;
    
    return (y);
}

unsigned char bcd2hex (unsigned char y) {
    return ((y>>4)*10)+ (y & 0x0F);
}