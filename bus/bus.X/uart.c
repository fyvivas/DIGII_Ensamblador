
#include <xc.h>
#include "uart.h"

void USART_Init(long baud_rate)
{
    //float temp;
    TRISC6=OUTPUT;                       /*Make Tx pin as output*/
    TRISC7=INPUT;                       /*Make Rx pin as input*/
    //temp=Baud_rate;
    SPBRG = 25;
    //SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x24;      //b'00100100'                /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;       //b'10010000'              /*Receive Enable(RX) enable and serial port enable */
}
/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TxChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}

void USART_SendString(const char *out)
{
   while(*out!='\0')
   {            
        USART_TxChar(*out);
        out++;
   }
}

