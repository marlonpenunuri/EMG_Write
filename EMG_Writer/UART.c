/*
 * File:   UART.c
 * Author: Marlon
 *
 * Created on October 8, 2017, 4:37 PM
 */

#include <xc.h>
#include "UART.h"

void config() {
    TXSTA=0x26;
    RCSTA=0x90;
    SPBRGH=0;   
    SPBRG=103;
    BAUDCON=0x48;
    TRISTX=1;
    TRISRX =1;
}

void putc_UART(unsigned char dato_TX) {
    while(TXSTAbits.TRMT==0);   
    TXREG=dato_TX;
}

unsigned char scanf_UART() {
  while(PIR1bits.RCIF==0);    
  PIR1bits.RCIF=0;
  return RCREG;
}

void printf_UART (unsigned char dato [] ) {
    unsigned char i=0;
    while(dato[i]!= '\0') { 
        putc_UART(dato[i]);
        i=i+1;
    }
}

void BCD_UART(unsigned char x) {
        putc_UART((x>>4)+0x30);   
        putc_UART((x & 0x0F)+0x30);
        
}