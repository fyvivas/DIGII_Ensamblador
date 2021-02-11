/* 
 * File:   pinout.h
 * Author: ASUS
 *
 * Created on 29 de octubre de 2020, 09:19 AM
 */

#ifndef PINOUT_H
#define	PINOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

// definicion de constantes
# define Boton_asc  0       //Definimos Led como RB0
# define Boton_dsc	1       //Definimos Led como RB1
//# define Switch_activar	 2    // Definimos Led como RB2
# define Boton_sub	3        //Definimos Led como RB3
# define Boton_baj	4       //Definimos Led como RB4    
# define flag_counter  0
# define flag_counter_inc 1  

# define Switch_activar	 RB2 //RC4 
                    
//# define FLAG_COUNTER_INC 1
# define OUTPUT	 1 //RC4
# define INPUT	 0 //RC4

# define LOW	 0
# define HIGH	 1

# define APAGADO	 0
# define ENCENDIDO 1

# define DISPLAY_UNITS	 RA1
# define DISPLAY_TENS RA0
    
#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */

