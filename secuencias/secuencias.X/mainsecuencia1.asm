
#include "p16F887.inc"    
; CONFIG1
; __config 0x28D5
 __CONFIG _CONFIG1, _FOSC_INTRC_CLKOUT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_OFF & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0x3FFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF

  LIST p=16F887
   
N EQU 0x40
cont1 EQU 0x20
cont2 EQU 0x21
cont3 EQU 0x22
var EQU 0x23
varEfecto EQU 0x24
 
    ORG	0x00
    GOTO INICIO
  
INICIO
    BCF STATUS,RP0   ;RP0 = 0
    BCF STATUS,RP1  ;RP1 = 0
    CLRF PORTA	;PORTA = 0
    CLRF PORTD ;PORT SECUENCIA LED
    ;MOVLW B'0000000'  ;
    ;MOVWF PORTA
    BSF STATUS, RP0 ;RP0 = 1
    CLRF TRISA
    CLRF TRISD	;SECUENCIA SALIDA
    BSF STATUS,RP1
    CLRF ANSEL
    BCF STATUS,RP0  ;BANK O RP1=0 RP0=0
    BCF STATUS,RP1
    BSF TRISB,0
    
    
BOTON
    BTFSC PORTB,0
    GOTO BOTON
    CALL RETARDO
    BTFSC PORTB,0
    GOTO BOTON
    GOTO EFECTO
    
EFECTO
    INCF varEfecto
    
    
    

    MOVLW 0x01
    MOVWF PORTD

LOOP
    MOVLW 16
    MOVWF var
    
    
SECUENCIA1
    RLF PORTD
    CALL RETARDO
    DECFSZ var,1
    GOTO SECUENCIA1
   
    
    MOVLW 16
    MOVWF var
SECUENCIA2
    RRF PORTD
    CALL RETARDO
    DECFSZ var,1
    GOTO SECUENCIA2
    
    MOVLW 0xF0
    MOVWF PORTD


    MOVLW 16
    MOVWF var    
SECUENCIA4
    SWAPF PORTD
    CALL RETARDO
    DECFSZ var,1
    GOTO SECUENCIA4
    
    MOVLW 0xCC
    MOVWF PORTD

    MOVLW 16
    MOVWF var

SECUENCIA5
    SWAPF PORTD
    RRF PORTD
    CALL RETARDO
    DECFSZ var,1
    GOTO SECUENCIA5
 
    
RETARDO
    MOVLW N
    MOVWF cont1
    
REP_1
    MOVLW N
    MOVWF cont2
    
REP_2
    DECFSZ cont2,1
    GOTO REP_2
    DECFSZ cont1,1
    GOTO REP_1
    RETURN
   
    END

