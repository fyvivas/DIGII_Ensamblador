/* 
 * File:   uart.h
 * Author: ASUS
 *
 * Created on 29 de octubre de 2020, 09:43 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

# define OUTPUT	 0
# define INPUT	 1

# define LOW	 0
# define HIGH	 1
    
void USART_Init(long baud_rate);
void USART_TxChar(char out);
void USART_SendString(const char *out);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

