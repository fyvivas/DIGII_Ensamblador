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


void USART_Init(long);
void USART_TxChar(char);
void USART_SendString(const char *);
char USART_RxChar();

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)


//***Define the signal pins of all four displays***//
#define s1 RE0
#define s2 RE1

//***End of definition**////

void main(){
unsigned int a,b,c,d,e,f,g,h; //just variables
int i = 0; //the 4-digit value that is to be displayed
int flag =0; //for creating delay

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

//*****I/O Configuration****//
TRISE=0X00;
PORTE=0X00;
TRISD=0x00;
PORTD=0X00;
//***End of I/O configuration**///
//TRISAbits.TRISA0=1;//el pin RA0 como entrada digital  
//TRISBbits.TRISB3=0;//el pin RB3 como salida digital
//TRISBbits.TRISB4=0;//el pin RB4 como salida digital
    
//PORTBbits.RB3=0;//el led en el pin RB3 inicia apagado
//PORTBbits.RB4=0;//el led en el pin RB4 inicia encendido



#define _XTAL_FREQ 20000000
//int F = 0;

//for(int i=0;i<5;i++){
//    F++;
   
//}

//do{
//    led_enc();
    
//}while(F == 1);

while(1)
{
    //a = 24;
    //a=a%10; //4 units
    //a=a/10; //2 Tens
    
    
    //***Splitting "i" into four digits***//  
    a=i%10;//4th digit is saved here
    b=i/10;
    c=b%10;//3rd digit is saved here
    d=b/10;
    e=d%10; //2nd digit is saved here
    f=d/10;
    g=f%10; //1st digit is saved here
    h=f/10;
    //***End of splitting***//

    PORTD=seg[a];
    s1=1; //Turn ON display 1 and print 4th digit
    __delay_ms(5);
    s1=0;     //Turn OFF display 1 after 5ms delay
    PORTD=seg[c];
    s2=1; //Turn ON display 2 and print 3rd digit
    __delay_ms(5);
    s2=0;     //Turn OFF display 2 after 5ms delay

    if(flag>=100) //wait till flag reaches 100
    {
        i++;flag=0; //only if flag is hundred "i" will be incremented 
    }
    flag++; //increment flag for each flash
    }
}


/*****************************USART Initialization*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=Baud_value;     
    SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
}
/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TxChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}
/*******************RECEIVE FUNCTION*****************************************/
char USART_RxChar()
{
   
    
    while(RCIF==0);                 /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);                  /*receive data is stored in RCREG register and return to main program */
}

void USART_SendString(const char *out)
{
   while(*out!='\0')
   {            
        USART_TxChar(*out);
        out++;
   }
}
