#include <xc.h>
#include "comm.h"
#include "uart.h"
#include "setup_Up.h"
 
unsigned char Volt_in;
unsigned char i;


void configureGPIO (){ 
    TRISB = 0x00; 
    TRISDbits.RD1 = 0;
} 


void configureADC(void){ //Configuramos los registros necesarios para utilizar el ADC
        ADCON0=0X09;
    ADCON1=0X00;
        ADCON2=0x0C;  
}


void delay_ms (unsigned int ms){
    unsigned int timer_val;
    timer_val = (ms * 47 );
    timer_val = (unsigned int)65535 - timer_val;
    TMR0 = timer_val;
    T0CON =0x87;
    
    while(!INTCONbits.TMR0IF);
    T0CONbits.TMR0ON= 0;
    INTCONbits.TMR0IF= 0;
}


void conv(void){ //Funcion de conversion que pone el pin GODONE en 1
        ADCON0bits.GODONE=1;
        //while(ADCON0bits.GODONE==1);
   // PORTDbits.RD1 ^= 1;  
} 


unsigned char letra []= {' ','<','>','E','A','O','S','R','R','I','D','L','C',
'T','U','M','P','B','G', 'V','Y','Q','H','F','Z','J','Ñ','X','K','W' }; //[30]




void defInt(){ 
    INTCON = 0xC0; //(1100 0000)                                 
    INTCON2 = 0xF0; //(1111 0000)
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
}

void interrupt interrupcion() {
   if(ADRESH >= 128){
    delay_ms (250);
    
    if(i == 1){
        putc_UART(0x08);
        putc_UART(0x08);
    }
    
    if(i == 2) {
        putc_UART(0x08);
        putc_UART(0x20);
        putc_UART(0x20);
    }
    
    else{
        putc_UART(letra[i]);
    }
    
    INTCONbits.TMR0IF= 1;
    i = 0;
    }

    PIR1bits.ADIF = 0;
}




void ABCdario(){
    i = 0;
    
    while(1){
        putc_UART(letra[i]);
        delay_sec();
        i++;
        putc_UART(0x08);
        
        if (i>29) {
            i= 0;
        }
    }    
}


void main(void) {
    defInt();
    config();
    configureADC();
    configureGPIO();
    
    printf_UART("\n\rSeleccione las letras:\n\r");
    
    while(1){
        ABCdario();
    }
}