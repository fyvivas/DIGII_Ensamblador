; CONFIG1
; __config 0xF8F1
 __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_OFF & _FCMEN_ON & _LVP_ON
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
    
    
    LIST p=16F887
    INCLUDE <P16F887.INC>

; NOTA:
; Oscilador utilizado 4MHz.-
; ************************************************

; ------------------------------C�digo modificado-------------------------------------
; inicio
          org     0x00
          goto    inicio
          org     0x04
          goto    INTER

; Se transmite via Serie el dato que esta en el registro W
TX_DATO   bcf     PIR1,TXIF      ; Restaura el flag del transmisor
          movf numpasajeros,w
	  movwf   TXREG          ; Mueve el byte a transmitir al registro de transmision
          bsf     STATUS,RP0     ; Bank01
          bcf     STATUS,RP1

TX_DAT_W  btfss   TXSTA,TRMT     ; �Byte transmitido?
          goto    TX_DAT_W       ; No, esperar
          bcf     STATUS,RP0     ; Si, vuelta a Bank00
          return

; Tratamiento de interrupci�n
INTER     btfss   PIR1,RCIF      ; �Interrupci�n por recepci�n?
          goto    VOLVER         ; No, falsa interrupci�n
          bcf     PIR1,RCIF      ; Si, reponer flag
          movf    RCREG,W        ; Lectura del dato recibido
          movwf   PORTB          ; Visualizaci�n del dato
          call    TX_DATO        ; Transmisi�n del dato como eco
VOLVER    retfie

; Comienzo del programa principal
inicio    clrf    PORTB          ; Limpiar salidas
          clrf    PORTC
          bsf     STATUS,RP0     ; Bank01
          bcf     STATUS,RP1
          clrf    TRISB          ; PORTB como salida
          movlw   b'10111111'    ; RC7/RX entrada,
          movwf   TRISC          ; RC6/TX salida
          movlw   b'00100100'    ; Configuraci�n USART
          movwf   TXSTA          ; y activaci�n de transmisi�n
          movlw   .25            ; 9600 baudios
          movwf   SPBRG
          bsf     PIE1,RCIE      ; Habilita interrupci�n en recepci�n
          bcf     STATUS,RP0     ; Bank00
          movlw   b'10010000'    ; Configuraci�n del USART para recepci�n continua
          movwf   RCSTA          ; Puesta en ON
          movlw   b'11000000'    ; Habilitaci�n de las
          movwf   INTCON         ; interrupciones en general

BUCLE     nop
          goto    BUCLE

          end




