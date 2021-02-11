// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "pinout.h"
#include "uart.h"

//unsigned char Contador1 = 0; // 0 -255 // 8 bits
/*
char //0-127 bit7 (+, -))
int // 16 bits
long //32 bits
double // 32 bits
float // 32 bits (entera y decimal) 24/10 = 2.4
*/

unsigned int seg[]={0X3F, //Hex value to display the number 0
                    0X06, //Hex value to display the number 1
                    0X5B, //Hex value to display the number 2
                    0X4F, //Hex value to display the number 3
                    0X66, //Hex value to display the number 4
                    0X6D, //Hex value to display the number 5
                    0X7C, //Hex value to display the number 6
                    0X07, //Hex value to display the number 7
                    0X7F, //Hex value to display the number 8
                    0X6F  //Hex value to display the number 9
                   }; //End of Array for displaying numbers from 0 to 9



unsigned char DISP_COUNTER = 0;
unsigned char DISP_DEFAULT = 0x0c;
unsigned char DISP_FREQ = 0x20;
unsigned char STD_COUNTER = 0x01;
unsigned char NUMERO_PASAJEROS = 0;
unsigned char UMBRAL_BAJO = 0;
unsigned char UMBRAL_MEDIO = 0;
unsigned char UMBRAL_ALTO = 0;
unsigned char LIMITE_BAJO = 4;
unsigned char Hundred = 0;
unsigned char Tens = 0;
unsigned char Units = 0;	
unsigned char count8 = 0;
unsigned char temp = 0;

void setting1();
void run();
void sendData();


void main(){
    
    setup();
    
    while(1){
        loop();
    }
}



void main(){
    
    TRISD=0X00;
    TRISA=0x00;
    TRISB = 0x1F; //B'00011111';
    TRISC = 0xB8;
    ANSEL = 0;
    ANSELH = 0;
    PORTA=0X00;
    PORTD=0X00;
    PORTC=0X00;
    USART_Init(9600);
    STD_COUNTER = STD_COUNTER | (1 << flag_counter );
    //0000 0000
    //0000 0001
    //0000 0001
    STD_COUNTER = STD_COUNTER | (1 << flag_counter_inc );
    //0000 0000
    //0000 0010
    //0000 0010
    Binary2BCD(0);
    
    while(1){
    
        if(Switch_activar == HIGH){
            setting1();//configuracion
        }
        else{
            run();//ejecucion
        }
    }
    
}

void setting1(){
    
    Binary2BCD(DISP_COUNTER);
    PORTD=seg[Units];
    DISPLAY_UNITS = ENCENDIDO; //Turn ON display 1 and print 4th digit
    __delay_ms(20);
    DISPLAY_UNITS= APAGADO;     //Turn OFF display 1 after 5ms delay
    PORTD=seg[Tens];
    DISPLAY_TENS =ENCENDIDO; //Turn ON display 2 and print 3rd digit
    __delay_ms(20);
    DISPLAY_TENS=APAGADO;     //Turn OFF display 2 after 5ms delay
}


void run(){
    
    
    Binary2BCD(NUMERO_PASAJEROS);
    PORTD=seg[Units];
    RA1 =1; //Turn ON display 1 and print 4th digit
    __delay_ms(20);
    RA1=0;     //Turn OFF display 1 after 5ms delay
    PORTD=seg[Tens];
    RA0 =1; //Turn ON display 2 and print 3rd digit
    __delay_ms(20);
    RA0=0;     //Turn OFF display 2 after 5ms delay
    sendData();
}

void sendData(){
    Tens = Tens + 0x30;
    USART_TxChar(Tens);
    Units = Units + 0x30;
    USART_TxChar(Units);
    USART_TxChar('\r');
    USART_TxChar('\n');
}

//CONVERTER BINARY TO BCD
void Binary2BCD(unsigned char bin){
    //***Splitting "i" into four digits***//  bin = 56 
    Units=bin%10;//units digit is saved here 56%10 = 6 residuo
    Tens=bin/10;//tnes digit is saved here 56/10 = 5 entero
  
}